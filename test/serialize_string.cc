#include <gtest/gtest.h>
#include <pocketjson/pocketjson.h>

TEST(SerializeString, TestEmpty) {
    pocketjson::Value v = "";
    EXPECT_STREQ("\"\"", v.serialize().c_str());
}
TEST(SerializeString, TestString) {
    pocketjson::Value v = "hello world!";
    EXPECT_STREQ("\"hello world!\"", v.serialize().c_str());
}
TEST(SerializeString, TestEscapeString) {
    pocketjson::Value v = "\\hello\tworld!\n\r";
    EXPECT_STREQ("\"\\\\hello\\tworld!\\n\\r\"", v.serialize().c_str());
}
TEST(SerializeString, TestUnicodeString) {
    pocketjson::Value v = "\a";
    EXPECT_STREQ("\"\\u0007\"", v.serialize().c_str());
}
