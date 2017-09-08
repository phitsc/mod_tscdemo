
#include "httpd.h"
#include "http_config.h"
#include "http_protocol.h"

#include <string>

static int tscdemo_handler(request_rec* r)
{
    std::string userAgentAndIP(r->useragent_ip);

    ap_set_content_type(r, "text/html");
    ap_rputs("<p>Hello, Apache Module++!</p>", r);
    ap_rprintf(r, "<p>User Agent: %s</p>", userAgentAndIP.c_str());
    ap_rprintf(r, "<p>File: %s</p>", r->filename);

    return OK;
}

static void register_hooks(apr_pool_t* pool)
{
    ap_hook_handler(tscdemo_handler, NULL, NULL, APR_HOOK_LAST);
}

module AP_MODULE_DECLARE_DATA   tscdemo_module =
{
    STANDARD20_MODULE_STUFF,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    register_hooks
};
