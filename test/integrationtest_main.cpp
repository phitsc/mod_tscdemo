#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "Curl.hpp"

#include <iostream>
#include <string>

Curl curl;

TEST_CASE("Integration Tests", "[mod_tscdemo]")
{
    const char* indexPage = R"(<meta name="mod_tscdemo" content="index-page">)";
    const char* errorPage = R"(<meta name="mod_tscdemo" content="error-page">)";

    REQUIRE(
        curl.get("http://localhost/index.html")
        .find(indexPage) != std::string::npos
    );

    REQUIRE(
        curl.get("http://localhost/anyfile.html?name=philipp&hello=world")
        .find(errorPage) == std::string::npos
    ); // *should not* be the error page

    REQUIRE(
       curl.get("http://localhost/anyfile.html?name=philipp&hello=barbapapa&field=value")
       .find(errorPage) != std::string::npos
   ); // now it *should* be the error page
}
