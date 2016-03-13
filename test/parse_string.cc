#include <gtest/gtest.h>
#include <pocketjson/pocketjson.h>

TEST(ParseString, TestEmpty) {
    pocketjson::Value v;
    EXPECT_TRUE(pocketjson::parse(v, "\"\""));
    EXPECT_TRUE(v.isString());
    EXPECT_STREQ("", v.as<std::string>().c_str());
}
TEST(ParseString, TestEscapeString) {
    pocketjson::Value v;
    EXPECT_TRUE(pocketjson::parse(v, "\"Escape \\t \\n\\r  \\b\\f \\/\\\\.\""));
    EXPECT_TRUE(v.isString());
    EXPECT_STREQ("Escape \t \n\r  \b\f /\\.", v.as<std::string>().c_str());
}
TEST(ParseString, TestUnicodeString) {
    pocketjson::Value v;
    EXPECT_TRUE(pocketjson::parse(v, "\"Unicode \\u3042\n\\uD867\\uDe3d露\""));
    EXPECT_TRUE(v.isString());
    EXPECT_STREQ("Unicode あ\n𩸽露", v.as<std::string>().c_str());
}
TEST(ParseString, TestNumberString) {
    pocketjson::Value v;
    EXPECT_TRUE(pocketjson::parse(v, "\"123\""));
    EXPECT_TRUE(v.isString());
    EXPECT_STREQ("123", v.as<std::string>().c_str());
    EXPECT_EQ(123, v.toInt(10));
}

TEST(ParseString, TestStringFail) {
    pocketjson::Value v = 123;
    EXPECT_FALSE(pocketjson::parse(v, "\"abc"));
    EXPECT_FALSE(pocketjson::parse(v, "\"\\ \""));
    EXPECT_FALSE(pocketjson::parse(v, "\"\\a \""));
    EXPECT_TRUE(v.isNumber());
}
