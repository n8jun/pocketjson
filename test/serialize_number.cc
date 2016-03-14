#include <gtest/gtest.h>
#include <pocketjson/pocketjson.h>

TEST(SerializeNumber, Test0) {
    pocketjson::Value v = 0;
    EXPECT_STREQ("0", v.serialize().c_str());
}
TEST(SerializeNumber, Test1) {
    pocketjson::Value v = 1;
    EXPECT_STREQ("1", v.serialize().c_str());
}
TEST(SerializeNumber, TestMinus1) {
    pocketjson::Value v = -1;
    EXPECT_STREQ("-1", v.serialize().c_str());
}
TEST(SerializeNumber, Test0f) {
    pocketjson::Value v = 0.0;
    EXPECT_STREQ("0.0", v.serialize().c_str());
}
TEST(SerializeNumber, TestFloat) {
    pocketjson::Value v = 0.5;
    EXPECT_STREQ("0.5", v.serialize().c_str());
    v = 16.0;
    EXPECT_STREQ("16", v.serialize().c_str());
    v = -1.25;
    EXPECT_STREQ("-1.25", v.serialize().c_str());
}

TEST(SerializeNumber, TestFail) {
    pocketjson::Value v = INFINITY;
    std::string s;
    EXPECT_FALSE(v.serialize(std::back_inserter(s)));
}
