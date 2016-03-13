#include <gtest/gtest.h>
#include <pocketjson/pocketjson.h>

TEST(ParseArray, TestEmpty) {
    pocketjson::Value v;
    EXPECT_TRUE(pocketjson::parse(v, "\n[]\t"));
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(0, v.size());
    v = 123;
    EXPECT_TRUE(pocketjson::parse(v, "\n[\n\r  ]\t"));
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(0, v.size());
}
TEST(ParseArray, TestSimpleArray) {
    pocketjson::Value v;
    EXPECT_TRUE(pocketjson::parse(v, "[\nnull,null,\n true,false, null ]"));
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(5, v.size());
    EXPECT_TRUE(v[0].isNull());
    EXPECT_TRUE(v[1].isNull());
    EXPECT_TRUE(v[2].isBoolean());
    EXPECT_TRUE(v[2].as<bool>());
    EXPECT_TRUE(v[3].isBoolean());
    EXPECT_FALSE(v[3].as<bool>());
    EXPECT_TRUE(v[4].isNull());
}
TEST(ParseArray, TestNestedArray) {
    pocketjson::Value v;
    EXPECT_TRUE(pocketjson::parse(v, "[\n1, { \"foo\": 3},\n [3, 4, [], 1.23], \"str\", null ]"));
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(5, v.size());
    EXPECT_TRUE(v[0].isInteger());
    EXPECT_EQ(1, v[0].as<int64_t>());
    EXPECT_TRUE(v[1].isObject());
    EXPECT_EQ(1, v[1].size());
    EXPECT_EQ(3, v[1]["foo"].toInt());
    EXPECT_TRUE(v[2].isArray());
    EXPECT_EQ(4, v[2].size());
    EXPECT_EQ(3, v[2][0].toInt());
    EXPECT_EQ(4, v[2][1].toInt());
    EXPECT_TRUE(v[2][2].isArray());
    EXPECT_TRUE(v[2][2].empty());
    EXPECT_TRUE(v[3].isString());
    EXPECT_STREQ("str", v[3].toString().c_str());
    EXPECT_TRUE(v[4].isNull());
}

TEST(ParseArray, TestFail) {
    pocketjson::Value v;
    EXPECT_FALSE(pocketjson::parse(v, "\n[123,  123"));
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(2, v.size());
    v = 123;
    EXPECT_FALSE(pocketjson::parse(v, "\n[null,]\t"));
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(1, v.size());
}
TEST(ParseArray, TestCommaEnding) {
    pocketjson::Value v;
    EXPECT_TRUE(pocketjson::parse(v, "\n[null, \n]\t", pocketjson::kParseOptionAllowCommaEnding));
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(1, v.size());
}
