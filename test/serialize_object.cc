#include <gtest/gtest.h>
#include <pocketjson/pocketjson.h>

TEST(SerializeObject, TestEmpty) {
    pocketjson::Value v(pocketjson::kObject);
    EXPECT_STREQ("{}", v.serialize().c_str());
}
TEST(SerializeObject, TestObject) {
    pocketjson::Value v;
    v["a"].setNull();
    v["b"] = true;
    v["c"][0] = -0.5;
    v["d"].setType(pocketjson::kObject);
    v["e"] = "hello";
    v["nest"]["key"] = "value";
    const char* expected = "{\"a\":null,\"b\":true,\"c\":[-0.5],\"d\":{},\"e\":\"hello\",\"nest\":{\"key\":\"value\"}}";
    EXPECT_STREQ(expected, v.serialize().c_str());
}
TEST(SerializeObject, TestPretty) {
    pocketjson::Value v;
    v["a"].setNull();
    v["b"] = true;
    v["c"][0] = -0.5;
    v["d"].setType(pocketjson::kObject);
    v["e"] = "hello";
    v["nest"]["key"] = "value";
    const char* expected =
        "{\n"
        "  \"a\": null,\n"
        "  \"b\": true,\n"
        "  \"c\": [\n"
        "    -0.5\n"
        "  ],\n"
        "  \"d\": {},\n"
        "  \"e\": \"hello\",\n"
        "  \"nest\": {\n"
        "    \"key\": \"value\"\n"
        "  }\n"
        "}";
    EXPECT_STREQ(expected, v.serialize(pocketjson::kSerializeOptionPretty).c_str());
}
TEST(SerializeObject, TestPretty4Spaces) {
    pocketjson::Value v;
    v["a"].setNull();
    v["b"] = true;
    v["c"][0] = -0.5;
    v["d"].setType(pocketjson::kObject);
    v["e"] = "hello";
    v["nest"]["key"] = "value";
    const char* expected =
        "{\n"
        "    \"a\": null,\n"
        "    \"b\": true,\n"
        "    \"c\": [\n"
        "        -0.5\n"
        "    ],\n"
        "    \"d\": {},\n"
        "    \"e\": \"hello\",\n"
        "    \"nest\": {\n"
        "        \"key\": \"value\"\n"
        "    }\n"
        "}";
    EXPECT_STREQ(expected, v.serialize(pocketjson::kSerializeOptionPretty4Spaces).c_str());
}
TEST(SerializeObject, TestPrettyTab) {
    pocketjson::Value v;
    v["a"].setNull();
    v["b"] = true;
    v["c"][0] = -0.5;
    v["d"].setType(pocketjson::kObject);
    v["e"] = "hello";
    v["nest"]["key"] = "value";
    const char* expected =
        "{\n"
        "\t\"a\": null,\n"
        "\t\"b\": true,\n"
        "\t\"c\": [\n"
        "\t\t-0.5\n"
        "\t],\n"
        "\t\"d\": {},\n"
        "\t\"e\": \"hello\",\n"
        "\t\"nest\": {\n"
        "\t\t\"key\": \"value\"\n"
        "\t}\n"
        "}";
    EXPECT_STREQ(expected, v.serialize(pocketjson::kSerializeOptionPrettyTab).c_str());
}
