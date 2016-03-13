#include <gtest/gtest.h>
#include <pocketjson/pocketjson.h>

TEST(ParseNumber, Test0) {
    pocketjson::Value v;
    EXPECT_TRUE(pocketjson::parse(v, "0"));
    EXPECT_TRUE(v.isNumber());
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(0, v.as<int64_t>());
    EXPECT_EQ(false, v.toBoolean(true));
    EXPECT_EQ(0, v.toInt(1));
    EXPECT_EQ(0, v.toUInt(1));
    EXPECT_STREQ("0", v.toString().c_str());
}
TEST(ParseNumber, TestMinus0) {
    pocketjson::Value v;
    EXPECT_TRUE(pocketjson::parse(v, "-0"));
    EXPECT_TRUE(v.isNumber());
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(0, v.as<int64_t>());
    EXPECT_EQ(false, v.toBoolean(true));
    EXPECT_EQ(0, v.toInt(1));
    EXPECT_EQ(0, v.toUInt(1));
    EXPECT_STREQ("0", v.toString("null").c_str());
}
TEST(ParseNumber, Test1) {
    pocketjson::Value v;
    EXPECT_TRUE(pocketjson::parse(v, "1"));
    EXPECT_TRUE(v.isNumber());
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(1, v.as<int64_t>());
    EXPECT_EQ(true, v.toBoolean(false));
    EXPECT_EQ(1, v.toUInt(0));
    EXPECT_EQ(1, v.toInt(0));
    EXPECT_STREQ("1", v.toString("null").c_str());
}
TEST(ParseNumber, Test1f) {
    pocketjson::Value v;
    EXPECT_TRUE(pocketjson::parse(v, "1.0"));
    EXPECT_TRUE(v.isNumber());
    EXPECT_TRUE(v.isFloat());
    EXPECT_EQ(1.0, v.as<double>());
    EXPECT_EQ(true, v.toBoolean(false));
    EXPECT_EQ(1, v.toUInt(0));
    EXPECT_EQ(1.0, v.toDouble(0.2));
    EXPECT_STREQ("1", v.toString("null").c_str());
}
TEST(ParseNumber, TestLLongMax) {
    pocketjson::Value v;
    EXPECT_TRUE(pocketjson::parse(v, "9223372036854775807"));
    EXPECT_TRUE(v.isNumber());
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(9223372036854775807ULL, v.as<int64_t>());
    EXPECT_EQ(true, v.toBoolean(false));
    EXPECT_EQ(123, v.toInt(123));
    EXPECT_EQ(123, v.toUInt(123));
    EXPECT_EQ(9223372036854775807ULL, v.toULong(123));
    EXPECT_EQ(9223372036854775807ULL, v.toULLong(123));
    EXPECT_STREQ("9223372036854775807", v.toString("null").c_str());
}
TEST(ParseNumber, TestOverLLongMax) {
    pocketjson::Value v;
    EXPECT_TRUE(pocketjson::parse(v, "9223372036854775808"));
    EXPECT_TRUE(v.isNumber());
    EXPECT_TRUE(v.isFloat());
    EXPECT_EQ(9223372036854775808.0, v.as<double>());
    EXPECT_EQ(true, v.toBoolean(false));
    EXPECT_EQ(123, v.toInt(123));
    EXPECT_EQ(123, v.toUInt(123));
    EXPECT_EQ(9223372036854775808.0, v.toDouble(1.23));
    EXPECT_STREQ("9.2233720368547758e+18", v.toString("null").c_str());
}
TEST(ParseNumber, TestLLongMin) {
    pocketjson::Value v;
    EXPECT_TRUE(pocketjson::parse(v, "-9223372036854775807"));
    EXPECT_TRUE(v.isNumber());
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(-9223372036854775807LL, v.as<int64_t>());
    EXPECT_EQ(true, v.toBoolean(false));
    EXPECT_EQ(123, v.toShort(123));
    EXPECT_EQ(123, v.toULLong(123));
    EXPECT_EQ(-9223372036854775807LL, v.toLLong(-123));
    EXPECT_STREQ("-9223372036854775807", v.toString("null").c_str());
}
TEST(ParseNumber, TestUnderLLongMin) {
    pocketjson::Value v;
    EXPECT_TRUE(pocketjson::parse(v, "-9223372036854775808"));
    EXPECT_TRUE(v.isNumber());
    EXPECT_TRUE(v.isFloat());
    EXPECT_EQ(-9223372036854775808.0, v.as<double>());
    EXPECT_EQ(true, v.toBoolean(false));
    EXPECT_EQ(-9223372036854775808.0, v.toDouble(1.23));
    EXPECT_EQ(123, v.toInt(123));
    EXPECT_EQ(123, v.toULong(123));
    EXPECT_STREQ("-9.2233720368547758e+18", v.toString("null").c_str());
}
TEST(ParseNumber, TestFloat) {
    pocketjson::Value v;
    EXPECT_TRUE(pocketjson::parse(v, "3.1415"));
    EXPECT_TRUE(v.isNumber());
    EXPECT_TRUE(v.isFloat());
    EXPECT_EQ(3.1415, v.as<double>());
    EXPECT_EQ(3, v.toLLong(123));
    EXPECT_EQ(3.1415, v.toDouble(1.23));
    pocketjson::Value v2 = pocketjson::parse(v.toString("null"));
    EXPECT_EQ(v.as<double>(), v2.as<double>());
}
TEST(ParseNumber, TestFloatExp) {
    pocketjson::Value v;
    EXPECT_TRUE(pocketjson::parse(v, "-9.223372036e10"));
    EXPECT_TRUE(v.isNumber());
    EXPECT_TRUE(v.isFloat());
    EXPECT_EQ(-92233720360, v.as<double>());
    EXPECT_EQ(123, v.toShort(123));
    EXPECT_EQ(-92233720360, v.toLLong(123));
    EXPECT_EQ(-92233720360.0, v.toDouble(1.23));
    EXPECT_STREQ("-92233720360", v.toString("null").c_str());
}
TEST(ParseNumber, TestExpNumber) {
    pocketjson::Value v;
    EXPECT_TRUE(pocketjson::parse(v, "92e-3"));
    EXPECT_TRUE(v.isNumber());
    EXPECT_TRUE(v.isFloat());
    EXPECT_EQ(0.092, v.as<double>());
    EXPECT_EQ(0, v.toLLong(123));
    EXPECT_EQ(0.092, v.toDouble(1.23));
    pocketjson::Value v2 = pocketjson::parse(v.toString());
    EXPECT_EQ(v.as<double>(), v2.as<double>());

    EXPECT_TRUE(pocketjson::parse(v, "92e3"));
    EXPECT_TRUE(v.isNumber());
    EXPECT_TRUE(v.isFloat());
    EXPECT_EQ(92000.0, v.as<double>());
    EXPECT_EQ(92000, v.toLLong(123));
    EXPECT_EQ(92000.0, v.toDouble(1.23));

    EXPECT_TRUE(pocketjson::parse(v, "92e+1"));
    EXPECT_TRUE(v.isNumber());
    EXPECT_TRUE(v.isFloat());
    EXPECT_EQ(920.0, v.as<double>());
    EXPECT_EQ(920, v.toLLong(123));
    EXPECT_EQ(920.0, v.toDouble(1.23));

    EXPECT_TRUE(pocketjson::parse(v, "92e+0"));
    EXPECT_EQ(92, v.as<int64_t>());
    EXPECT_TRUE(pocketjson::parse(v, "92.1e0"));
    EXPECT_EQ(92.1, v.as<double>());
    EXPECT_TRUE(pocketjson::parse(v, "92.1e+0"));
    EXPECT_EQ(92.1, v.as<double>());
    EXPECT_TRUE(pocketjson::parse(v, "92.1e-0"));
    EXPECT_EQ(92.1, v.as<double>());
    EXPECT_TRUE(pocketjson::parse(v, "92e-0"));
    EXPECT_EQ(92, v.as<int64_t>());
}

TEST(ParseNumber, TestMinusFail) {
    pocketjson::Value v = true;
    EXPECT_FALSE(pocketjson::parse(v, "-.12"));
    EXPECT_FALSE(pocketjson::parse(v, "-e12"));
    EXPECT_FALSE(pocketjson::parse(v, "-a"));
    EXPECT_FALSE(pocketjson::parse(v, "-00.2"));
    EXPECT_FALSE(pocketjson::parse(v, "-1.e1"));
    EXPECT_TRUE(v.isBoolean());
}
TEST(ParseNumber, TestZeroFail) {
    pocketjson::Value v = true;
    EXPECT_FALSE(pocketjson::parse(v, "00"));
    EXPECT_FALSE(pocketjson::parse(v, "01"));
    EXPECT_FALSE(pocketjson::parse(v, "0.0e00"));
    EXPECT_FALSE(pocketjson::parse(v, "+0"));
    EXPECT_TRUE(v.isBoolean());
}
TEST(ParseNumber, TestExpFail) {
    pocketjson::Value v = true;
    EXPECT_FALSE(pocketjson::parse(v, "0e"));
    EXPECT_FALSE(pocketjson::parse(v, "0e+"));
    EXPECT_FALSE(pocketjson::parse(v, "0.0e-"));
    EXPECT_FALSE(pocketjson::parse(v, "e1"));
    EXPECT_FALSE(pocketjson::parse(v, "2E"));
    EXPECT_FALSE(pocketjson::parse(v, "3E+-123"));
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(pocketjson::parse(v, "2e0.1"));
    EXPECT_EQ(2, v.as<int64_t>());
}
