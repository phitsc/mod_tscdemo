
#include "httpd.h"
#include "http_config.h"
#include "http_protocol.h"

#include <algorithm>
#include <string>
#include <utility> // pair
#include <vector>

using StringPair = std::pair<std::string, std::string>;


std::vector<std::string> split(const std::string& s, const char* divider)
{
    std::vector<std::string> result;

    std::string::size_type lastPos = 0;
    auto pos = s.find(divider);

    while (pos != std::string::npos)
    {
        result.push_back(s.substr(lastPos, pos - lastPos));

        lastPos = pos + 1;
        pos = s.find(divider, pos + 1);
    }

    if (lastPos < s.size())
    {
        result.push_back(s.substr(lastPos));
    }

    return result;
}

struct Config
{
    std::vector<std::string> blacklist;
};

static Config config;

const char* parseBlacklist(cmd_parms* cmd, void* cfg, const char* arg)
{
    config.blacklist = split(arg, ",");

    return nullptr;
}

static const command_rec directives[] =
{
    AP_INIT_TAKE1("Blacklist", (cmd_func)parseBlacklist, nullptr, RSRC_CONF, "A list of values to blacklist."),
    { nullptr }
};

static int tscdemo_handler(request_rec* r)
{
    const std::string args(r->args != nullptr ? r->args : "");

    ap_set_content_type(r, "text/html");
    ap_rputs("<p>Hello, Apache Module++!</p>", r);

    ap_rputs("<p>Arguments:</p>", r);

    ap_rputs("<ul>", r);

    const auto argumentList = split(args, "&");
    std::vector<StringPair> fieldValueList(argumentList.size());

    std::transform(argumentList.begin(), argumentList.end(), fieldValueList.begin(),
        [](const std::string& s) -> StringPair
        {
            const auto fieldValue = split(s, "=");

            return fieldValue.size() == 1
                ? std::make_pair(fieldValue[0], "")
                : std::make_pair(fieldValue[0], fieldValue[1]);
        }
    );

    for (const auto& fieldValue : fieldValueList)
    {
        ap_rprintf(r, "<li>%s = %s</li>", fieldValue.first.c_str(), fieldValue.second.c_str());
    }

    ap_rputs("</ul>", r);

    ap_rputs("<p>Blacklist:</p>", r);

    ap_rputs("<ul>", r);


    for (const auto& term : config.blacklist)
    {
        ap_rprintf(r, "<li>%s</li>", term.c_str());
    }

    ap_rputs("</ul>", r);

    const auto it = std::find_first_of(
        fieldValueList.begin(), fieldValueList.end(),
        config.blacklist.begin(), config.blacklist.end(),
        [](const StringPair& fieldValue, const std::string& term)
        {
            return fieldValue.second == term;
        }
    );

    if (it != fieldValueList.end())
    {
        ap_rprintf(r, "<p>Found %s</p>", it->second.c_str());
    }

    return OK;
}

static void register_hooks(apr_pool_t* pool)
{
    ap_hook_handler(tscdemo_handler, nullptr, nullptr, APR_HOOK_LAST);
}

module AP_MODULE_DECLARE_DATA   tscdemo_module =
{
    STANDARD20_MODULE_STUFF,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    directives,
    register_hooks
};
