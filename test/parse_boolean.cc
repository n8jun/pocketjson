#include <gtest/gtest.h>
#include <pocketjson/pocketjson.h>

TEST(ParseBoolean, TestTrue) {
    pocketjson::Value v = 1;
    EXPECT_TRUE(pocketjson::parse(v, " true"));
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.as<bool>());
    EXPECT_TRUE(v.toBoolean());
    EXPECT_EQ(1, v.toInt(0));
    EXPECT_STREQ("true", v.toString("null").c_str());
}
TEST(ParseBoolean, TestFalse) {
    pocketjson::Value v = 0;
    EXPECT_TRUE(pocketjson::parse(v, " false"));
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.as<bool>());
    EXPECT_FALSE(v.toBoolean());
    EXPECT_EQ(0, v.toInt(1));
    EXPECT_STREQ("false", v.toString("null").c_str());
}

TEST(ParseBoolean, TestTrueFail) {
    pocketjson::Value v = "";
    EXPECT_FALSE(pocketjson::parse(v, " tree"));
    EXPECT_TRUE(v.isString());
}
TEST(ParseBoolean, TestFalseFail) {
    pocketjson::Value v = 0;
    EXPECT_FALSE(pocketjson::parse(v, " fals"));
    EXPECT_TRUE(v.isNumber());
}
