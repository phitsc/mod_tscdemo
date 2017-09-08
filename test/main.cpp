#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../src/split.hpp"

using vec = std::vector<std::string>;

TEST_CASE("Basics", "[split]")
{
    REQUIRE( split("", ',') == vec({ "" }) );
    REQUIRE( split("", ' ') == vec({ "" }) );
    REQUIRE( split("foo", ',') == vec({ "foo" }) );
    REQUIRE( split("foo,bar,baz", ',') == vec({ "foo", "bar", "baz" }) );
    REQUIRE( split("foo,bar,baz", '/') == vec({ "foo,bar,baz" }) );
    REQUIRE( split("foo,bar,baz", ' ') == vec({ "foo,bar,baz" }) );
    REQUIRE( split("foo,bar,baz", '+') == vec({ "foo,bar,baz" }) );
    REQUIRE( split("foo,,bar,,baz", ',') == vec({ "foo", "", "bar", "", "baz" }) );
    REQUIRE( split("foo,bar,baz,", ',') == vec({ "foo", "bar", "baz", "" }) );
}

TEST_CASE("Url", "[split]")
{
    REQUIRE( split("field1=value1", '&') == vec({ "field1=value1" }) );
    REQUIRE( split("field1=value1&field2=value2", '&') == vec({ "field1=value1", "field2=value2" }) );
    REQUIRE( split("field1=value1&field2=value2&field3=value3", '&') ==
        vec({ "field1=value1", "field2=value2", "field3=value3" })
    );
    REQUIRE( split("field1=value1&field2=value2&field3=value3&", '&') ==
        vec({ "field1=value1", "field2=value2", "field3=value3", "" })
    );
    REQUIRE( split("field1=value1&field2&field3=value3&", '&') ==
        vec({ "field1=value1", "field2", "field3=value3", "" })
    );
}

TEST_CASE("FieldValue", "[split]")
{
    REQUIRE( split("field1=value1", '=') == vec({ "field1", "value1" }) );
    REQUIRE( split("field1", '=') == vec({ "field1" }) );
    REQUIRE( split("field1=value1&field2=value2", '=') == vec({ "field1", "value1&field2", "value2" }) );
    REQUIRE( split("field1=value1=", '=') == vec({ "field1", "value1", "" }) );
    REQUIRE( split("=", '=') == vec({ "", "" }) );
    REQUIRE( split("===", '=') == vec({ "", "", "", "" }) );
    REQUIRE( split(" = ", '=') == vec({ " ", " " }) );
}

