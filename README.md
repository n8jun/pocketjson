# pocketjson
Header only JSON parser &amp; serializer for C++

[![Build Status](https://travis-ci.org/n8jun/pocketjson.svg?branch=master)](https://travis-ci.org/n8jun/pocketjson)

Copyright (c) 2016 Jun Nishimura

## Usage
Add and include `pocketjson.h` in your project to use pocketjson.
```
#include <pocketjson/pocketjson.h>
```
### Value
#### Set value
`pocketjson::Value` class prepares some setter functions.
Use `operator =` or `void set***()` to set value.
`operator []` is also available for Array or Object type.
These functions change value type automatically.
```
pocketjson::Value value; // null
value = true; // bool
value = 100; // number
value = "hello"; // string
value.setFloat(23.0); // float
value[0] = "array"; // array (automatically resize array)
value.push_back(123); // add array item
value["key"] = 3.14; // object (automatically insert key)
value.insert("name", "pocketjson"); // insert object pair
```
#### Check type
Use `bool is***() const` or `bool is<T>() const` function to check value type.
```
if (value.isObject()) {
    // value is object type.
}
if (value.is<std::string>()) {
    // value is string type.
}
```
#### Get value
Use `T to***() const` function to get value.
It can be set fallback value for nonconvertible value type.
Boolean, Integer, Float or String type value can convert to each other value type.
```
// "null" returns when value is null, array or object.
std::string str = value.toString("null");

// 0.0 returns when value is null, array or object.
double num = value.toDouble();
```

### Parse
pocketjson prepares DOM and SAX type parser.

#### Parse simply
```
const char* json = "{\"name\": \"pocketjson\"}";
pocketjson::Value value = pocketjson::parse(json);
```
#### Parse loose format JSON string
Set parse options to allow comma ending of object or array.
```
const char* json = "{\"name\": \"pocketjson\",}";
pocketjson::Value value = pocketjson::parse(json, pocketjson::kParseOptionAllowLooseFormat);
```
#### Get parse error
```
const char* json = "{\"name\": \"pocketjson\",}";
// Check with error message.
std::string err;
pocketjson::Value value = pocketjson::parse(json, pocketjson::kParseOptionNone, &err);
if (!err.empty()) {
    // Error
}

// Check bool.
if (!pocketjson::parse(value, json)) {
    // Error
}
```
#### Parse SAX type
It requires the following steps to use SAX type parser.
- Create your custom class derived from `pocketjson::AbstractParseHandler` class.
- Create instance of `pocketjson::Parser` class.
- Create instance of your custom parse handler class.
- Call `parse` function of `pocketjson::Parser` class.
```
class MyHandler: public pocketjson::AbstractParseHandler {
public:
    MyHandler() {}
    ~MyHandler() {}

public:
    virtual bool onNull() { printf("null\n"); return true; }
    virtual bool onBoolean(const bool& v) { printf("boolean: %s\n", v ? "true" : "false"); return true; }
    virtual bool onInteger(const int64_t& v) { printf("integer: %lld\n", v); return true; }
    virtual bool onFloat(const double& v) { printf("float: %f\n", v); return true; }
    virtual bool onString(const String& v) { printf("string: %s\n", v.c_str()); return true; }
    virtual bool beginArray() { printf("begin array\n"); return true; }
    virtual bool endArray(const size_t& count) { printf("end array: %lu\n", count); return true; }
    virtual bool beginObject() { printf("begin object\n"); return true; }
    virtual bool onObjectKey(const String& key) { printf("object key: %s\n", key.c_str()); return true; }
    virtual bool endObject(const size_t& count) { printf("end object: %lu\n", count); return true; }
}; // MyHandler class

const char* json = "{\"name\": \"pocketjson\"}";
pocketjson::Parser p;
MyHandler handler;
if (!p.parse(&handler, json)) {
    // Error
}
```
### Serialize
`pocketjson::Value` class has `std::string serialize() const` function which supports pretty options.
```
pocketjson::Value value;
value["name"] = "pocketjson";
std::string json = value.serialize();
std::string prettyJson = value.serialize(pocketjson::kSerializeOptionPretty);
```

## License
Distributed under the [Boost Software License, Version 1.0](http://www.boost.org/LICENSE_1_0.txt).
