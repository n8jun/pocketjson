#include <gtest/gtest.h>
#include <pocketjson/pocketjson.h>

TEST(SerializeBoolean, TestTrue) {
    pocketjson::Value v = true;
    EXPECT_STREQ("true", v.serialize().c_str());
}
TEST(SerializeBoolean, TestFalse) {
    pocketjson::Value v = false;
    EXPECT_STREQ("false", v.serialize().c_str());
}
