#include <gtest/gtest.h>
#include <pocketjson/pocketjson.h>

TEST(SerializeArray, TestEmpty) {
    pocketjson::Value v(pocketjson::kArray);
    EXPECT_STREQ("[]", v.serialize().c_str());
}
TEST(SerializeArray, TestArray) {
    pocketjson::Value v;
    v[0].setNull();
    v[1] = true;
    v[2][0] = -0.5;
    v[3].setType(pocketjson::kObject);
    v[4] = "hello";
    v[5]["key"] = "value";
    const char* expected = "[null,true,[-0.5],{},\"hello\",{\"key\":\"value\"}]";
    EXPECT_STREQ(expected, v.serialize().c_str());
}
