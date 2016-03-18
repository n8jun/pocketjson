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
```
pocketjson::Value value; // null
value = true; // bool
value = 100; // number
value = "hello"; // string
value[0] = "array"; // array
value.push_back(123); // add array item
value["key"] = 3.14; // object
value.insert("name", "pocketjson"); // add object item
```
#### Check type
Use `bool Value::is***() const` function to check value type.
```
if (value.isObject()) {
    // value is object type.
}
```
#### Get value
Use `type Value::to***() const` function to get value.
It can be set fallback value for different value type.
```
// "null" returns when value is not string type.
std::string str = value.toString("null");
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

// Check bool.
if (!pocketjson::parse(value, json)) {
    // Error
}
```
#### Parse SAX type
Create your custom class derived from `pocketjson::AbstractParseHandler` class.
```
class MyHandler: public pocketjson::AbstractParseHandler {
public:
    MyHandler() {}
    ~MyHandler() {}

public:
    virtual bool onNull() {
        printf("null\n");
        return true;
    }
    virtual bool onBoolean(const bool& v) {
        printf("boolean: %d\n", v);
        return true;
    }
    virtual bool onInteger(const int64_t& v) {
        printf("integer: %lld\n", v);
        return true;
    }
    virtual bool onFloat(const double& v) {
        printf("float: %f\n", v);
        return true;
    }
    virtual bool onString(const String& v) {
        printf("string: %s\n", v.c_str());
        return true;
    }
    virtual bool beginArray() {
        printf("begin array\n");
        return true;
    }
    virtual bool endArray(const size_t& count) {
        printf("end array: %d\n", int(count));
        return true;
    }
    virtual bool beginObject() {
        printf("begin object\n");
        return true;
    }
    virtual bool onObjectKey(const String& key) {
        printf("object key: %s\n", key.c_str());
        return true;
    }
    virtual bool endObject(const size_t& count) {
        printf("end object: %d\n", int(count));
        return true;
    }
};

pocketjson::Parser p;
MyHandler handler;
p.parse(&handler);
```
### Serialize
```
pocketjson::Value value;
value["name"] = "pocketjson";
std::string json = value.serialize();
std::string prettyJson = value.serialize(pocketjson::kSerializeOptionPretty);
```

## License
Distributed under the [Boost Software License, Version 1.0](http://www.boost.org/LICENSE_1_0.txt).
