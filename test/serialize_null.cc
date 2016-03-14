#include <gtest/gtest.h>
#include <pocketjson/pocketjson.h>

TEST(SerializeNull, TestNull) {
    pocketjson::Value v;
    EXPECT_STREQ("null", v.serialize().c_str());
}
