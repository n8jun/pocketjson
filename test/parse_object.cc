#include <gtest/gtest.h>
#include <pocketjson/pocketjson.h>

TEST(ParseObject, TestEmpty) {
    pocketjson::Value v;
    EXPECT_TRUE(pocketjson::parse(v, "\n{}\t"));
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(0, v.size());
    v = 123;
    EXPECT_TRUE(pocketjson::parse(v, "\n{\n\r  }\t"));
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(0, v.size());
}
TEST(ParseObject, TestSimpleObject) {
    pocketjson::Value v;
    EXPECT_TRUE(pocketjson::parse(v, "{ \"bool\"\n:\ntrue\n, \"int\":123,\"string\":\"hello\", \"array\":[], \"null\":null}\n"));
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(5, v.size());
    EXPECT_TRUE(v["null"].isNull());
    EXPECT_TRUE(v["bool"].isBoolean());
    EXPECT_TRUE(v["bool"].toBoolean(false));
    EXPECT_TRUE(v["int"].isInteger());
    EXPECT_EQ(123, v["int"].toInt());
    EXPECT_TRUE(v["string"].isString());
    EXPECT_STREQ("hello", v["string"].toString().c_str());
    EXPECT_TRUE(v["array"].isArray());
    EXPECT_TRUE(v["array"].empty());
}
TEST(ParseObject, TestNestedObject) {
    pocketjson::Value v;
    EXPECT_TRUE(pocketjson::parse(v, "{ \"nest\":\n{\"deep\": {\"key\": -456}}, \"array\": [{\"name\": \"pocketjson\"}]}\n"));
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(2, v.size());
    EXPECT_TRUE(v["nest"].isObject());
    EXPECT_TRUE(v["nest"]["deep"].isObject());
    EXPECT_TRUE(v["nest"]["deep"]["key"].isInteger());
    EXPECT_EQ(-456, v["nest"]["deep"]["key"].toInt());
    EXPECT_TRUE(v["array"].isArray());
    EXPECT_EQ(1, v["array"].size());
    EXPECT_TRUE(v["array"][0].isObject());
    EXPECT_TRUE(v["array"][0]["name"].isString());
    EXPECT_STREQ("pocketjson", v["array"][0]["name"].toString().c_str());
}

TEST(ParseObject, TestFail) {
    pocketjson::Value v;
    EXPECT_FALSE(pocketjson::parse(v, "\n{\"a\":123,  \"b\":123"));
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(2, v.size());
    v = 123;
    EXPECT_FALSE(pocketjson::parse(v, "\n{\"a\":null,   }\t"));
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(1, v.size());
}
TEST(ParseObject, TestCommaEnding) {
    pocketjson::Value v;
    EXPECT_TRUE(pocketjson::parse(v, "{\"a\":null,   }", pocketjson::kParseOptionAllowCommaEnding));
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(1, v.size());
}
