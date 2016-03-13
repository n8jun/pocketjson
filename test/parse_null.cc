#include <gtest/gtest.h>
#include <pocketjson/pocketjson.h>

TEST(ParseNull, TestNull) {
    pocketjson::Value v = true;
    EXPECT_TRUE(pocketjson::parse(v, "\n  \tnull\r "));
    EXPECT_TRUE(v.isNull());
    EXPECT_EQ(true, v.toBoolean(true));
    EXPECT_STREQ("null", v.toString("null").c_str());
}

TEST(ParseNull, TestNullFail) {
    pocketjson::Value v = true;
    EXPECT_FALSE(pocketjson::parse(v, "nil\r\n"));
    EXPECT_TRUE(v.isBoolean());
}

TEST(ParseNull, TestNullGabage) {
    pocketjson::Value v = true;
    EXPECT_FALSE(pocketjson::parse(v, "\n  \tnull1234"));
    EXPECT_TRUE(v.isNull());
    v = 123;
    EXPECT_TRUE(pocketjson::parse(v, "\n  \tnull1234", pocketjson::kParseOptionAllowGabage));
    EXPECT_TRUE(v.isNull());
}
