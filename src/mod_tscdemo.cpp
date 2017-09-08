
#include "httpd.h"
#include "http_config.h"
#include "http_protocol.h"

#include "split.hpp"

#include <algorithm>
#include <string>
#include <utility> // pair
#include <vector>

using StringPair = std::pair<std::string, std::string>;

// Holds configuration data
struct Config
{
    std::vector<std::string> blacklist;
};

static Config config;

// Parse comma-separated list of blacklisted terms specified in httpd.conf
// using the Blacklist config entry
const char* parseBlacklist(cmd_parms* cmd, void* cfg, const char* arg)
{
    config.blacklist = split(arg, ',');

    return nullptr;
}

static const command_rec directives[] =
{
    AP_INIT_TAKE1("Blacklist", (cmd_func)parseBlacklist, nullptr, RSRC_CONF, "A list of values to blacklist."),
    { nullptr }
};

// The main module handler. Handles every server request with arguments specified, i.e. 
// something like somefile.html?someField=value
static int tscdemo_handler(request_rec* r)
{
    if (!r->args)
    {
        return DECLINED;
    }

    ap_set_content_type(r, "text/html");
    ap_rputs("<p>Hello, Apache Module++!</p>", r);

    ap_rputs("<p>Arguments:</p>", r);

    ap_rputs("<ul>", r);

    // Parse and split arguments and put them into a vector so they can
    // be compared against the list of blacklisted terms.
    const auto argumentList = split(r->args, '&');
    std::vector<StringPair> fieldValueList(argumentList.size());

    // Now split the field names and the field values.
    // Only field values are considered for blacklisting, not field names.
    std::transform(argumentList.begin(), argumentList.end(), fieldValueList.begin(),
        [](const std::string& s)
        {
            const auto fieldValue = split(s, '=');

            return fieldValue.size() == 1
                ? std::make_pair(fieldValue[0], "")
                : std::make_pair(fieldValue[0], fieldValue[1]);
        }
    );

    // Print list of arguments
    for (const auto& fieldValue : fieldValueList)
    {
        ap_rprintf(r, "<li>%s = %s</li>", fieldValue.first.c_str(), fieldValue.second.c_str());
    }

    ap_rputs("</ul>", r);

    // Print list of blacklist terms
    ap_rputs("<p>Blacklist:</p>", r);

    ap_rputs("<ul>", r);

    for (const auto& term : config.blacklist)
    {
        ap_rprintf(r, "<li>%s</li>", term.c_str());
    }

    ap_rputs("</ul>", r);

    // Find the first field value containing (substring match) any of the
    // blacklisted terms.
    const auto it = std::find_first_of(
        fieldValueList.begin(), fieldValueList.end(),
        config.blacklist.begin(), config.blacklist.end(),
        [](const StringPair& fieldValue, const std::string& term)
        {
            return fieldValue.second.find(term) != std::string::npos;
        }
    );

    if (it != fieldValueList.end())
    {
        ap_rprintf(r, "<p>Found blacklisted term <b>%s</b></p>", it->second.c_str());
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
