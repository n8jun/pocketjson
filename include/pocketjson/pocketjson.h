#ifndef POCKETJSON_H
#define POCKETJSON_H

#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <string>
#include <vector>
#include <map>

#if (__has_feature(cxx_rvalue_references) \
    || defined(__GXX_EXPERIMENTAL_CXX0X__) \
    || (defined(_MSC_VER) && _MSC_VER >= 1600))
#define _POCKETJSON_HAS_RVALUE_REFERENCES
#endif

namespace pocketjson {

class Value;
typedef std::string String;
typedef std::vector<Value> Array;
typedef std::map<String, Value> Object;

enum Type {
    kNull     = 0x00,
    kBoolean  = 0x01,
    kInteger  = 0x02,
    kFloat    = 0x04,
    kNumber   = kInteger | kFloat,
    kString   = 0x10,
    kObject   = 0x20,
    kArray    = 0x40,
    kContainer = kString | kObject | kArray
}; // Type enum

enum ParseOptions {
    kParseOptionNone = 0x00,
    kParseOptionAllowCommaEnding = 0x01,
    kParseOptionAllowGabage = 0x02,
    kParseOptionAllowLooseFormat = kParseOptionAllowCommaEnding | kParseOptionAllowGabage
}; // ParseOptions enum

enum SerializeOptions {
    kSerializeOptionNone    = 0x00,
    kSerializeOptionPretty  = 0x80,
    kSerializeOption2Spaces = 0x00,
    kSerializeOption4Spaces = 0x01,
    kSerializeOptionTab     = 0x02,
    kSerializeOptionTabMask = 0x03,
    kSerializeOptionLineBreakCRLF = 0x04
}; // SerializeOptions enum

/**
 * Json value class.
 */
class Value {
public:
    Value();
    Value(const bool& v);
    Value(const char& v);
    Value(const short& v);
    Value(const int& v);
    Value(const long& v);
    Value(const long long& v);
    Value(const unsigned char& v);
    Value(const unsigned short& v);
    Value(const unsigned int& v);
    Value(const unsigned long& v);
    Value(const unsigned long long& v);
    Value(const float& v);
    Value(const double& v);
    Value(const char* v);
    Value(const String& v);
    Value(const Array& v);
    Value(const Object& v);
    Value(const Type& type);
    Value(const Value& v);
    ~Value();

public:
    Value& operator =(const bool& rhs);
    Value& operator =(const char& rhs);
    Value& operator =(const short& rhs);
    Value& operator =(const int& rhs);
    Value& operator =(const long& rhs);
    Value& operator =(const long long& rhs);
    Value& operator =(const unsigned char& rhs);
    Value& operator =(const unsigned short& rhs);
    Value& operator =(const unsigned int& rhs);
    Value& operator =(const unsigned long& rhs);
    Value& operator =(const unsigned long long& rhs);
    Value& operator =(const float& rhs);
    Value& operator =(const double& rhs);
    Value& operator =(const char* rhs);
    Value& operator =(const String& rhs);
    Value& operator =(const Array& rhs);
    Value& operator =(const Object& rhs);
    Value& operator =(const Value& rhs);

#ifdef _POCKETJSON_HAS_RVALUE_REFERENCES
    Value(Value&& v);
    Value& operator =(Value&& rhs);
#endif

public:
    static const Value& Null();

public:
    Value& operator [](const String& key);
    const Value& operator [](const String& key) const;
    Value& operator [](const size_t& index);
    const Value& operator [](const size_t& index) const;

public:
    void push_back(const Value& v);
    void pop_back();
    void insert(const String& key, const Value& v);
    void erase(const String& key);
    void clear();

    void setType(const Type& t);
    void setBoolean(const bool& v);
    void setInteger(const char& v);
    void setInteger(const short& v);
    void setInteger(const int& v);
    void setInteger(const long& v);
    void setInteger(const long long& v);
    void setInteger(const unsigned char& v);
    void setInteger(const unsigned short& v);
    void setInteger(const unsigned int& v);
    void setInteger(const unsigned long& v);
    void setInteger(const unsigned long long& v);
    void setFloat(const float& v);
    void setFloat(const double& v);
    void setString(const String& v);
    void setArray(const Array& v);
    void setObject(const Object& v);

public:
    template<typename StringType>
    bool serialize(StringType& str, const SerializeOptions& options = kSerializeOptionNone, String* errorMessage = 0) const;
    String serialize(const SerializeOptions& options = kSerializeOptionNone, String* errorMessage = 0) const;

public:
    const Type& type() const;
    bool isNull() const;
    bool isBoolean() const;
    bool isInteger() const;
    bool isFloat() const;
    bool isNumber() const;
    bool isString() const;
    bool isArray() const;
    bool isObject() const;

    bool toBoolean(const bool& defaults = false) const;
    char toChar(const char& defaults = 0) const;
    short toShort(const short& defaults = 0) const;
    int toInt(const int& defaults = 0) const;
    long toLong(const long& defaults = 0) const;
    long long toLLong(const long long& defaults = 0) const;
    unsigned char toUChar(const unsigned char& defaults = 0) const;
    unsigned short toUShort(const unsigned short& defaults = 0) const;
    unsigned int toUInt(const unsigned int& defaults = 0) const;
    unsigned long toULong(const unsigned long& defaults = 0) const;
    unsigned long long toULLong(const unsigned long long& defaults = 0) const;
    float toFloat(const float& defaults = 0.0f) const;
    double toDouble(const double& defaults = 0.0) const;
    String toString(const String& defaults = "") const;

    bool empty() const;
    size_t size() const;
    bool contains(const String& key) const;
    bool contains(const size_t& index) const;

    template<typename T> T& as();
    template<typename T> const T& as() const;

private:
    void release();

private:
    class AbstractContainer;
    template<typename T> class Container;

private:
    Type type_;
    union {
        bool boolean_;
        int64_t integer_;
        double float_;
        AbstractContainer* container_;
    };

}; // Value class

/**
 * Abstract parse handler class.
 * Define and use a custom handler class when parsing Json with SAX.
 * All virtual functions return true when continue parsing.
 */
class AbstractParseHandler {
public:
    inline AbstractParseHandler() {}
    inline virtual ~AbstractParseHandler() {}

public:
    virtual bool onNull() = 0;
    virtual bool onBoolean(const bool& v) = 0;
    virtual bool onInteger(const int64_t& v) = 0;
    virtual bool onFloat(const double& v) = 0;
    virtual bool onString(const String& v) = 0;
    virtual bool beginArray() = 0;
    virtual bool endArray(const size_t& count) = 0;
    virtual bool beginObject() = 0;
    virtual bool onObjectKey(const String& key) = 0;
    virtual bool endObject(const size_t& count) = 0;

}; // AbstractParseHandler class

template<typename Iter>
inline Value parse(const Iter& begin, const Iter& end, const ParseOptions& options = kParseOptionNone, String* errorMessage = 0);
inline Value parse(const String& str, const ParseOptions& options = kParseOptionNone, String* errorMessage = 0);
template<typename Iter>
inline bool parse(Value& value, const Iter& begin, const Iter& end, const ParseOptions& options = kParseOptionNone, String* errorMessage = 0);
inline bool parse(Value& value, const String& str, const ParseOptions& options = kParseOptionNone, String* errorMessage = 0);


/*-----------------------------------------------------------
 * Inline implementation.
 *-----------------------------------------------------------*/
/**
 * Parser class
 */
class Parser {
public:
    inline Parser() {}
    inline ~Parser() {}

public:
    template<typename Iter> bool parse(Value& value, const Iter& begin, const Iter& end, const ParseOptions& options = kParseOptionNone, String* errorMessage = 0);
    template<typename Iter> bool parse(AbstractParseHandler* handler, const Iter& begin, const Iter& end, const ParseOptions& options = kParseOptionNone, String* errorMessage = 0);

private:
    template<typename Iter> bool parse(Value* value, AbstractParseHandler* handler, const Iter& begin, const Iter& end, const ParseOptions& options = kParseOptionNone, String* errorMessage = 0);

    template<typename Iter> bool parse_value(Value* value, AbstractParseHandler* handler, Iter& itr, const Iter& end, const ParseOptions& options);
    template<typename Iter> bool parse_number(Value* value, AbstractParseHandler* handler, Iter& itr, const Iter& end);
    template<typename Iter> bool parse_string(Value* value, AbstractParseHandler* handler, Iter& itr, const Iter& end);
    template<typename Iter> bool parse_hex(uint16_t& hex, Iter& itr, const Iter& end);
    template<typename Iter> bool parse_unicode(String& str, Iter& itr, const Iter& end);
    template<typename Iter> bool parse_string(String& str, Iter& itr, const Iter& end);
    template<typename Iter> bool parse_array(Value* value, AbstractParseHandler* handler, Iter& itr, const Iter& end, const ParseOptions& options);
    template<typename Iter> bool parse_object(Value* value, AbstractParseHandler* handler, Iter& itr, const Iter& end, const ParseOptions& options);
    template<typename CharType> bool is_white_space(const CharType& c);
    template<typename Iter> void skip_white_space(Iter& itr, const Iter& end);
    template<typename Iter> void skip_utf8_bom(Iter& itr, const Iter& end);

    bool fail(const String& error);

private:
    String lastError_;

}; // Parser class

class Serializer {
public:
    inline Serializer() {}
    inline ~Serializer() {}

public:
    template<typename StringType> bool serialize(StringType& str, const Value& value, const SerializeOptions& options = kSerializeOptionNone, String* errorMessage = 0) const;

public:
    template<typename StringType> static StringType& int64ToString(StringType& str, const int64_t& value);
    static String int64ToString(const int64_t& value);
    template<typename StringType> static StringType& uint64ToString(StringType& str, const uint64_t& value);
    static String uint64ToString(const uint64_t& value);

private:
    struct Attributes {
        bool pretty;
        String tab;
        String lineBreak;
    }; // Attributes struct

    template<typename StringType> bool serialize(StringType& str, const Value& value, const Attributes& attr, const int32_t& indentLevel, String* errorMessage = 0) const;
    template<typename StringType> void serialize_string(StringType& str, const String& value) const;
    template<typename StringType> void indent(StringType& str, const Attributes& attr, const int32_t& indent) const;
    template<typename StringType> void append(StringType& str, const String& app) const;

}; // Serializer class

class Double {
public:
    inline Double(): u_(0) {}
    inline Double(const double& d): d_(d) {}
    inline Double(const uint64_t& u): u_(u) {}
    inline ~Double() {}

public:
    inline int32_t sign() const { return isMinus() ? -1 : 1; }
    inline uint64_t significand() const { return u_ & kSignificandMask; }
    inline int32_t exponent() const { return static_cast<int32_t>((u_ & kExponentMask) >> kSignificandBitSize) - kExponentBias; }

    inline bool isMinus() const { return u_ & kSignMask; }
    inline bool isZero() const { return (u_ & (kExponentMask | kSignificandMask)) == 0; }
    inline bool isNan() const { return isNanOrInf() && significand() != 0; }
    inline bool isInf() const { return isNanOrInf() && significand() == 0; }
    inline bool isNanOrInf() const { return (u_ & kExponentMask) == kExponentMask; }

public:
    static const uint64_t kSignMask = 0x8000000000000000;
    static const uint64_t kExponentMask = 0x7ff0000000000000;
    static const uint64_t kSignificandMask = 0x000fffffffffffff;
    static const int32_t kSignificandBitSize = 52;
    static const int32_t kExponentBias = 0x3ff;

    template<typename StringType>
    inline bool toString(StringType& str) const {
        if (isZero()) {
            str.push_back('0'); str.push_back('.'); str.push_back('0');
            return true;
        } else if (isNan()) {
            str.push_back('n'); str.push_back('a'); str.push_back('n');
            return false;
        } else if (isInf()) {
            if (isMinus()) { str.push_back('-'); }
            str.push_back('i'); str.push_back('n'); str.push_back('f');
            return false;
        } else {
            char buf[128] = {0};
#ifdef _MSC_VER
            const auto s = _snprintf_s(buf, 127, _TRUNCATE, "%.17g", d_);
#else
            const auto s = snprintf(buf, 127, "%.17g", d_);
#endif
            for (int i = 0; i < s; ++i) {
                str.push_back(buf[i]);
            }
            return true;
        }
    }
    inline String toString() const {
        String str; this->toString(str); return str;
    }

private:
    union {
        double d_;
        uint64_t u_;
    };
}; // Double class

class CodePoint {
public:
    inline CodePoint(): value_(0) {}
    inline CodePoint(const uint16_t& u1, const uint16_t& u2): value_(u1) {
        if (u2) {
            value_ = ((u1 - 0xd800) << 10) + ((u2 - 0xdc00) & 0x3ff) + 0x10000;
        }
    }
    inline CodePoint(const uint32_t& v): value_(v) {}
    inline ~CodePoint() {}

public:
    template<typename StringType>
    inline void toUtf8(StringType& str) const {
        if (value_ < 0x80) {
            this->to7BitUtf8(str);
        } else if (value_ < 0x0800) {
            this->to11BitUtf8(str);
        } else if (value_ < 0x010000) {
            this->to16BitUtf8(str);
        } else {
            this->to21BitUtf8(str);
        }
    }

private:
    template<typename StringType>
    inline void to7BitUtf8(StringType& str) const {
        str.push_back(bytes_[0]);
    }
    template<typename StringType>
    inline void to11BitUtf8(StringType& str) const {
        str.push_back(0xc0 | (value_ >> 6));
        str.push_back(0x80 | (bytes_[0] & 0x3f));
    }
    template<typename StringType>
    inline void to16BitUtf8(StringType& str) const {
        str.push_back(0xe0 | (value_ >> 12));
        str.push_back(0x80 | ((value_ >> 6) & 0x3f));
        str.push_back(0x80 | (bytes_[0] & 0x3f));
    }
    template<typename StringType>
    inline void to21BitUtf8(StringType& str) const {
        str.push_back(0xf0 | (value_ >> 18));
        str.push_back(0x80 | ((value_ >> 12) & 0x3f));
        str.push_back(0x80 | ((value_ >> 6) & 0x3f));
        str.push_back(0x80 | (bytes_[0] & 0x3f));
    }

private:
    union {
        uint32_t value_;
        uint8_t bytes_[4];
    };
}; // CodePoint class

/**
 * Value class implementation.
 */
class Value::AbstractContainer {
public:
    inline AbstractContainer(): referenceCount_(1) {}
    inline virtual ~AbstractContainer() {}

public:
    inline void increment() { ++referenceCount_; }
    inline bool decrement() { return --referenceCount_ == 0; }
    template<typename T> inline const T& data() const;
    template<typename T> inline T& data();

private:
    uint32_t referenceCount_;
}; // Value::AbstractContainer class

template<typename T>
class Value::Container: public AbstractContainer {
public:
    inline Container(): AbstractContainer(), data_() {}
    inline Container(const T& data): AbstractContainer(), data_(data) {}
    inline ~Container() {}

public:
    inline const T& data() const { return data_; }
    inline T& data() { return data_; }

private:
    T data_;
}; // Value::Container class

template<typename T> inline const T& Value::AbstractContainer::data() const {
    return reinterpret_cast<const Container<T>*>(this)->data();
}
template<typename T> inline T& Value::AbstractContainer::data() {
    return reinterpret_cast<Container<T>*>(this)->data();
}

inline Value::Value(): type_(kNull), integer_(0) {}
inline Value::Value(const bool& v): type_(kBoolean), boolean_(v) {}
inline Value::Value(const char& v): type_(kInteger), integer_(v) {}
inline Value::Value(const short& v): type_(kInteger), integer_(v) {}
inline Value::Value(const int& v): type_(kInteger), integer_(v) {}
inline Value::Value(const long& v): type_(kInteger), integer_(v) {}
inline Value::Value(const long long& v): type_(kInteger), integer_(static_cast<long long>(v)) {}
inline Value::Value(const unsigned char& v): type_(kInteger), integer_(static_cast<long long>(v)) {}
inline Value::Value(const unsigned short& v): type_(kInteger), integer_(static_cast<long long>(v)) {}
inline Value::Value(const unsigned int& v): type_(kInteger), integer_(static_cast<long long>(v)) {}
inline Value::Value(const unsigned long& v): type_(kInteger), integer_(static_cast<long long>(v)) {}
inline Value::Value(const unsigned long long& v): type_(kInteger), integer_(static_cast<long long>(v)) {}
inline Value::Value(const float& v): type_(kFloat), float_(v) {}
inline Value::Value(const double& v): type_(kFloat), float_(v) {}
inline Value::Value(const char* v): type_(kString), container_(new Container<String>(v)) {}
inline Value::Value(const String& v): type_(kString), container_(new Container<String>(v)) {}
inline Value::Value(const Array& v): type_(kArray), container_(new Container<Array>(v)) {}
inline Value::Value(const Object& v): type_(kObject), container_(new Container<Object>(v)) {}
inline Value::Value(const Type& type): type_(type), integer_(0) {
    switch (type) {
    case kString: container_ = new Container<String>(); break;
    case kObject: container_ = new Container<Object>(); break;
    case kArray: container_ = new Container<Array>(); break;
    default: break;
    };
}
inline Value::Value(const Value& v): type_(v.type_), integer_(v.integer_) {
    if (type_ & kContainer) { container_->increment(); }
}
inline Value::~Value() { this->release(); }

inline Value& Value::operator =(const bool& rhs) { this->setBoolean(rhs); return *this; }
inline Value& Value::operator =(const char& rhs) { this->setInteger(rhs); return *this; }
inline Value& Value::operator =(const short& rhs) { this->setInteger(rhs); return *this; }
inline Value& Value::operator =(const int& rhs) { this->setInteger(rhs); return *this; }
inline Value& Value::operator =(const long& rhs) { this->setInteger(rhs); return *this; }
inline Value& Value::operator =(const long long& rhs) { this->setInteger(rhs); return *this; }
inline Value& Value::operator =(const unsigned char& rhs) { this->setInteger(rhs); return *this; }
inline Value& Value::operator =(const unsigned short& rhs) { this->setInteger(rhs); return *this; }
inline Value& Value::operator =(const unsigned int& rhs) { this->setInteger(rhs); return *this; }
inline Value& Value::operator =(const unsigned long& rhs) { this->setInteger(rhs); return *this; }
inline Value& Value::operator =(const unsigned long long& rhs) { this->setInteger(rhs); return *this; }
inline Value& Value::operator =(const float& rhs) { this->setFloat(rhs); return *this; }
inline Value& Value::operator =(const double& rhs) { this->setFloat(rhs); return *this; }
inline Value& Value::operator =(const char* rhs) { this->setString(rhs); return *this; }
inline Value& Value::operator =(const String& rhs) { this->setString(rhs); return *this; }
inline Value& Value::operator =(const Array& rhs) { this->setArray(rhs); return *this; }
inline Value& Value::operator =(const Object& rhs) { this->setObject(rhs); return *this; }
inline Value& Value::operator =(const Value& rhs) {
    if (this != &rhs) {
        this->release();
        type_ = rhs.type_;
        integer_ = rhs.integer_;
        if (type_ & kContainer) { container_->increment(); }
    }
    return *this;
}

#ifdef _POCKETJSON_HAS_RVALUE_REFERENCES
inline Value::Value(Value&& v): type_(v.type_), integer_(v.integer_) { v.integer_ = 0; }
inline Value& Value::operator =(Value&& rhs) {
    if (this != &rhs) {
        type_ = rhs.type_;
        integer_ = rhs.integer_;
        rhs.integer_ = 0;
    }
    return *this;
}
#endif

inline const Value& Value::Null() { static Value null; return null; }

inline Value& Value::operator [](const String& key) {
    this->setType(kObject);
    return container_->data<Object>()[key];
}
inline const Value& Value::operator [](const String& key) const {
    if (this->isObject()) {
        const auto& object = container_->data<Object>();
        const auto itr = object.find(key);
        return itr != object.end() ? itr->second : Value::Null();
    } else {
        return Value::Null();
    }
}
inline Value& Value::operator [](const size_t& index) {
    this->setType(kArray);
    auto& array = container_->data<Array>();
    if (index >= array.size()) {
        array.resize(index + 1);
    }
    return array[index];
}
inline const Value& Value::operator [](const size_t& index) const {
    if (this->isArray()) {
        auto& array = container_->data<Array>();
        return index < array.size() ? array[index] : Value::Null();
    } else {
        return Value::Null();
    }
}

inline void Value::push_back(const Value& v) {
    if (this != &v) {
        this->setType(kArray);
        container_->data<Array>().push_back(v);
    }
}
inline void Value::pop_back() {
    if (this->isArray()) {
        container_->data<Array>().pop_back();
    }
}
inline void Value::insert(const String& key, const Value& v) {
    if (this != &v) {
        this->setType(kObject);
        container_->data<Object>().insert(std::make_pair(key, v));
    }
}
inline void Value::erase(const String& key) {
    if (this->isObject()) {
        container_->data<Object>().erase(key);
    }
}

inline void Value::clear() {
    if (type_ != kNull) {
        this->release();
        type_ = kNull;
        integer_ = 0;
    }
}
inline void Value::setType(const Type& type) {
    if (type_ != type) {
        this->release();
        type_ = type;
        switch (type) {
        case kString: container_ = new Container<String>(); break;
        case kObject: container_ = new Container<Object>(); break;
        case kArray: container_ = new Container<Array>(); break;
        default: integer_ = 0; break;
        };
    }
}
#define _POCKETJSON_SET_PRIMITIVE_IMPL(type, target) this->release(); type_ = type; target = v
#define _POCKETJSON_SET_CAST_PRIMITIVE_IMPL(T, type, target) this->release(); type_ = type; target = static_cast<T>(v)
inline void Value::setBoolean(const bool& v) { _POCKETJSON_SET_PRIMITIVE_IMPL(kBoolean, boolean_); }
inline void Value::setInteger(const char& v) { _POCKETJSON_SET_PRIMITIVE_IMPL(kInteger, integer_); }
inline void Value::setInteger(const short& v) { _POCKETJSON_SET_PRIMITIVE_IMPL(kInteger, integer_); }
inline void Value::setInteger(const int& v) { _POCKETJSON_SET_PRIMITIVE_IMPL(kInteger, integer_); }
inline void Value::setInteger(const long& v) { _POCKETJSON_SET_PRIMITIVE_IMPL(kInteger, integer_); }
inline void Value::setInteger(const long long& v) { _POCKETJSON_SET_PRIMITIVE_IMPL(kInteger, integer_); }
inline void Value::setInteger(const unsigned char& v) { _POCKETJSON_SET_CAST_PRIMITIVE_IMPL(long long, kInteger, integer_); }
inline void Value::setInteger(const unsigned short& v) { _POCKETJSON_SET_CAST_PRIMITIVE_IMPL(long long, kInteger, integer_); }
inline void Value::setInteger(const unsigned int& v) { _POCKETJSON_SET_CAST_PRIMITIVE_IMPL(long long, kInteger, integer_); }
inline void Value::setInteger(const unsigned long& v) { _POCKETJSON_SET_CAST_PRIMITIVE_IMPL(long long, kInteger, integer_); }
inline void Value::setInteger(const unsigned long long& v) { _POCKETJSON_SET_CAST_PRIMITIVE_IMPL(long long, kInteger, integer_); }
inline void Value::setFloat(const float& v) { _POCKETJSON_SET_PRIMITIVE_IMPL(kFloat, float_); }
inline void Value::setFloat(const double& v) { _POCKETJSON_SET_PRIMITIVE_IMPL(kFloat, float_); }
#undef _POCKETJSON_SET_CAST_PRIMITIVE_IMPL
#undef _POCKETJSON_SET_PRIMITIVE_IMPL
#define _POCKETJSON_SET_CONAINER_IMPL(type, classType) if (type_ == type) { container_->data<classType>() = v; } else { this->release(); type_ = type; container_ = new Container<classType>(v); }
inline void Value::setString(const String& v) { _POCKETJSON_SET_CONAINER_IMPL(kString, String); }
inline void Value::setArray(const Array& v) { _POCKETJSON_SET_CONAINER_IMPL(kArray, Array); }
inline void Value::setObject(const Object& v) { _POCKETJSON_SET_CONAINER_IMPL(kObject, Object); }
#undef JSON_SET_CONAINER_IMPL

template<typename StringType>
inline bool Value::serialize(StringType& str, const SerializeOptions& options, String* errorMessage) const {
    Serializer s; return s.serialize(str, *this, options, errorMessage);
}
inline String Value::serialize(const SerializeOptions& options, String* errorMessage) const {
    String s; this->serialize(s, options, errorMessage); return s;
}

inline const Type& Value::type() const { return type_; }
inline bool Value::isNull() const { return type_ == kNull; }
inline bool Value::isBoolean() const { return type_ == kBoolean; }
inline bool Value::isInteger() const { return type_ == kInteger; }
inline bool Value::isFloat() const { return type_ == kFloat; }
inline bool Value::isNumber() const { return type_ & kNumber; }
inline bool Value::isString() const { return type_ == kString; }
inline bool Value::isArray() const { return type_ == kArray; }
inline bool Value::isObject() const { return type_ == kObject; }

inline bool Value::toBoolean(const bool& defaults) const {
    switch (type_) {
    case kBoolean: return boolean_;
    case kInteger: return integer_ != 0;
    case kFloat: return float_ != 0.0;
    case kString: return container_->data<String>() == "true";
    default: break;
    }
    return defaults;
}
inline bool is_range(const int64_t& value, const int64_t& minValue, const int64_t& maxValue) {
    return minValue <= value && value <= maxValue;
}
template<typename T>
inline T double_to_value(const double& value, const double& minValue, const double& maxValue, const T& defaults) {
    const auto d = round(value);
    return minValue <= d && d <= maxValue ? static_cast<T>(d) : defaults;
}
template<typename T>
inline T llstr_to_value(const String& str, const T& minValue, const T& maxValue, const T& defaults) {
    char* endp = 0;
    const auto value = strtoll(str.c_str(), &endp, 0);
    return endp == str.c_str() + str.size() && is_range(value, minValue, maxValue) ? static_cast<T>(value) : defaults;
}

inline char Value::toChar(const char& defaults) const {
    switch (type_) {
    case kInteger: return is_range(integer_, CHAR_MIN, CHAR_MAX) ? static_cast<char>(integer_) : defaults;
    case kFloat: return double_to_value<char>(float_, CHAR_MIN, CHAR_MAX, defaults);
    case kBoolean: return boolean_ ? 1 : 0;
    case kString: return llstr_to_value<char>(container_->data<String>(), CHAR_MIN, CHAR_MAX, defaults);
    default: break;
    }
    return defaults;
}
inline short Value::toShort(const short& defaults) const {
    switch (type_) {
    case kInteger: return is_range(integer_, SHRT_MIN, SHRT_MAX) ? static_cast<short>(integer_) : defaults;
    case kFloat: return double_to_value<short>(float_, SHRT_MIN, SHRT_MAX, defaults);
    case kBoolean: return boolean_ ? 1 : 0;
    case kString: return llstr_to_value<short>(container_->data<String>(), SHRT_MIN, SHRT_MAX, defaults);
    default: break;
    }
    return defaults;
}
inline int Value::toInt(const int& defaults) const {
    switch (type_) {
    case kInteger: return is_range(integer_, INT_MIN, INT_MAX) ? static_cast<int>(integer_) : defaults;
    case kFloat: return double_to_value<int>(float_, INT_MIN, INT_MAX, defaults);
    case kBoolean: return boolean_ ? 1 : 0;
    case kString: return llstr_to_value<int>(container_->data<String>(), INT_MIN, INT_MAX, defaults);
    default: break;
    }
    return defaults;
}
inline long Value::toLong(const long& defaults) const {
    switch (type_) {
    case kInteger: return is_range(integer_, LONG_MIN, LONG_MAX) ? static_cast<long>(integer_) : defaults;
    case kFloat: return double_to_value<long>(float_, LONG_MIN, LONG_MAX, defaults);
    case kBoolean: return boolean_ ? 1 : 0;
    case kString: return llstr_to_value<long>(container_->data<String>(), LONG_MIN, LONG_MAX, defaults);
    default: break;
    }
    return defaults;
}
inline long long Value::toLLong(const long long& defaults) const {
    switch (type_) {
    case kInteger: return static_cast<long long>(integer_);
    case kFloat: return double_to_value<long long>(float_, LLONG_MIN, LLONG_MAX, defaults);
    case kBoolean: return boolean_ ? 1 : 0;
    case kString: return llstr_to_value<long long>(container_->data<String>(), LLONG_MIN, LLONG_MAX, defaults);
    default: break;
    }
    return defaults;
}
inline unsigned char Value::toUChar(const unsigned char& defaults) const {
    switch (type_) {
    case kInteger: return is_range(integer_, 0, UCHAR_MAX) ? static_cast<unsigned char>(integer_) : defaults;
    case kFloat: return double_to_value<unsigned char>(float_, 0, UCHAR_MAX, defaults);
    case kBoolean: return boolean_ ? 1 : 0;
    case kString: return llstr_to_value<unsigned char>(container_->data<String>(), 0, UCHAR_MAX, defaults);
    default: break;
    }
    return defaults;
}
inline unsigned short Value::toUShort(const unsigned short& defaults) const {
    switch (type_) {
    case kInteger: return is_range(integer_, 0, USHRT_MAX) ? static_cast<unsigned short>(integer_) : defaults;
    case kFloat: return double_to_value<unsigned short>(float_, 0, USHRT_MAX, defaults);
    case kBoolean: return boolean_ ? 1 : 0;
    case kString: return llstr_to_value<unsigned short>(container_->data<String>(), 0, USHRT_MAX, defaults);
    default: break;
    }
    return defaults;
}
inline unsigned int Value::toUInt(const unsigned int& defaults) const {
    switch (type_) {
    case kInteger: return is_range(integer_, 0, UINT_MAX) ? static_cast<unsigned int>(integer_) : defaults;
    case kFloat: return double_to_value<unsigned int>(float_, 0, UINT_MAX, defaults);
    case kBoolean: return boolean_ ? 1 : 0;
    case kString: return llstr_to_value<unsigned int>(container_->data<String>(), 0, UINT_MAX, defaults);
    default: break;
    }
    return defaults;
}
inline unsigned long Value::toULong(const unsigned long& defaults) const {
    switch (type_) {
    case kInteger: return integer_ > 0 ? static_cast<unsigned long>(integer_) : defaults;
    case kFloat: return double_to_value<unsigned long>(float_, 0, ULONG_MAX, defaults);
    case kBoolean: return boolean_ ? 1 : 0;
    case kString: return llstr_to_value<unsigned long>(container_->data<String>(), 0, ULONG_MAX, defaults);
    default: break;
    }
    return defaults;
}
inline unsigned long long Value::toULLong(const unsigned long long& defaults) const {
    switch (type_) {
    case kInteger: return integer_ > 0 ? static_cast<unsigned long long>(integer_) : defaults;
    case kFloat: return double_to_value<unsigned long long>(float_, 0, ULLONG_MAX, defaults);
    case kBoolean: return boolean_ ? 1 : 0;
    case kString: return llstr_to_value<unsigned long long>(container_->data<String>(), 0, ULLONG_MAX, defaults);
    default: break;
    }
    return defaults;
}
inline float Value::toFloat(const float& defaults) const {
    switch (type_) {
    case kFloat: return static_cast<float>(float_);
    case kInteger: return static_cast<float>(integer_);
    case kBoolean: return boolean_ ? 1.0f : 0.0f;
    case kString: {
        char* endp = 0;
        const auto& str = container_->data<String>();
        const float value = static_cast<float>(strtod(str.c_str(), &endp));
        return endp == str.c_str() + str.size() ? value : defaults;
    }
    default: break;
    }
    return defaults;
}
inline double Value::toDouble(const double& defaults) const {
    switch (type_) {
    case kFloat: return float_;
    case kInteger: return static_cast<double>(integer_);
    case kBoolean: return boolean_ ? 1.0 : 0.0;
    case kString: {
        char* endp = 0;
        const auto& str = container_->data<String>();
        const double value = strtod(str.c_str(), &endp);
        return endp == str.c_str() + str.size() ? value : defaults;
    }
    default: break;
    }
    return defaults;
}
inline String Value::toString(const String& defaults) const {
    switch (type_) {
    case kString: return container_->data<String>();
    case kBoolean: return boolean_ ? "true" : "false";
    case kInteger: return Serializer::int64ToString(integer_);
    case kFloat: return Double(float_).toString();
    default: break;
    }
    return defaults;
}

inline bool Value::empty() const {
    switch (type_) {
    case kString: return container_->data<String>().empty();
    case kArray: return container_->data<Array>().empty();
    case kObject: return container_->data<Object>().empty();
    default: return true;
    }
}
inline size_t Value::size() const {
    switch (type_) {
    case kString: return container_->data<String>().size();
    case kArray: return container_->data<Array>().size();
    case kObject: return container_->data<Object>().size();
    default: return 0;
    }
}
inline bool Value::contains(const String& key) const {
    if (this->isObject()) {
        const auto& object = container_->data<Object>();
        return object.find(key) != object.end();
    }
    return false;
}
inline bool Value::contains(const size_t& index) const {
    if (this->isArray()) {
        return index < container_->data<Array>().size();
    }
    return false;
}

template<> inline bool& Value::as() { return boolean_; }
template<> inline const bool& Value::as() const { return boolean_; }
template<> inline int64_t& Value::as() { return integer_; }
template<> inline const int64_t& Value::as() const { return integer_; }
template<> inline double& Value::as() { return float_; }
template<> inline const double& Value::as() const { return float_; }
template<> inline String& Value::as() { return container_->data<String>(); }
template<> inline const String& Value::as() const { return container_->data<String>(); }
template<> inline Array& Value::as() { return container_->data<Array>(); }
template<> inline const Array& Value::as() const { return container_->data<Array>(); }
template<> inline Object& Value::as() { return container_->data<Object>(); }
template<> inline const Object& Value::as() const { return container_->data<Object>(); }

inline void Value::release() {
    if ((type_ & kContainer) && container_ && container_->decrement()) {
        delete container_;
        container_ = 0;
    }
}

template<typename Iter>
inline Value parse(const Iter& begin, const Iter& end, const ParseOptions& options, String* errorMessage) {
    Parser parser;
    Value value;
    parser.parse(value, begin, end, options, errorMessage);
    return value;
}
inline Value parse(const String& str, const ParseOptions& options, String* errorMessage) {
    return parse(str.begin(), str.end(), options, errorMessage);
}
template<typename Iter>
inline bool parse(Value& value, const Iter& begin, const Iter& end, const ParseOptions& options, String* errorMessage) {
    Parser parser;
    return parser.parse(value, begin, end, options, errorMessage);
}
inline bool parse(Value& value, const String& str, const ParseOptions& options, String* errorMessage) {
    return parse(value, str.begin(), str.end(), options, errorMessage);
}

/**
 * Parser class impelemtation.
 */
template<typename Iter>
inline bool Parser::parse(Value& value, const Iter& begin, const Iter& end, const ParseOptions& options, String* errorMessage) {
    return this->parse(&value, 0, begin, end, options, errorMessage);
}
template<typename Iter>
inline bool Parser::parse(AbstractParseHandler* handler, const Iter& begin, const Iter& end, const ParseOptions& options, String* errorMessage) {
    return this->parse(0, handler, begin, end, options, errorMessage);
}

template<typename Iter>
inline bool Parser::parse(Value* value, AbstractParseHandler* handler, const Iter& begin, const Iter& end, const ParseOptions& options, String* errorMessage) {
    lastError_.clear();
    Iter itr = begin;
    this->skip_utf8_bom(itr, end);
    bool ok = this->parse_value(value, handler, itr, end, options);
    if (ok) {
        if (!(options & kParseOptionAllowGabage)) {
            this->skip_white_space(itr, end);
            if (*itr != 0 && itr != end) {
                lastError_ = "Gabage string exists after json string.";
                ok = false;
            }
        }
    }
    if (errorMessage) { *errorMessage = lastError_; }
    return ok;
}

template<typename Iter>
inline bool Parser::parse_value(Value* value, AbstractParseHandler* handler, Iter& itr, const Iter& end, const ParseOptions& options) {
    this->skip_white_space(itr, end);
    if (*itr == '"') {
        return this->parse_string(value, handler, itr, end);
    } else if (*itr == '{') {
        return this->parse_object(value, handler, itr, end, options);
    } else if (*itr == '[') {
        return this->parse_array(value, handler, itr, end, options);
    } else if (*itr == '-' || ('0' <= *itr && *itr <= '9')) {
        return this->parse_number(value, handler, itr, end);
    } else if (*itr == 't') {
        if (*(++itr) == 'r' && *(++itr) == 'u' && *(++itr) == 'e') {
            if (value) {
                value->setBoolean(true);
            } else if (handler && !handler->onBoolean(true)) {
                return this->fail("SAX handler cancels parsing.");
            }
            ++itr;
            return true;
        } else {
            return this->fail("Invalid boolean type string exists.");
        }
    } else if (*itr == 'f') {
        if (*(++itr) == 'a' && *(++itr) == 'l' && *(++itr) == 's' && *(++itr) == 'e') {
            if (value) {
                value->setBoolean(false);
            } else if (handler && !handler->onBoolean(false)) {
                return this->fail("SAX handler cancels parsing.");
            }
            ++itr;
            return true;
        } else {
            return this->fail("Invalid boolean type string exists.");
        }
    } else if (*itr == 'n') {
        if (*(++itr) == 'u' && *(++itr) == 'l' && *(++itr) == 'l') {
            if (value) {
                value->clear();
            } else if (handler && !handler->onNull()) {
                return this->fail("SAX handler cancels parsing.");
            }
            ++itr;
            return true;
        } else {
            return this->fail("Invalid null type string exists.");
        }
    } else {
        return this->fail("Unexpected character exists while parsing.");
    }
}
template<typename Iter>
inline bool Parser::parse_number(Value* value, AbstractParseHandler* handler, Iter& itr, const Iter& end) {
    String str;
    bool isNegative = false;
    if (*itr == '-') {
        str.push_back(*itr);
        ++itr;
        isNegative = true;
    }
    bool isZeroAtFirst = *itr == '0';
    if (isZeroAtFirst) {
        str.push_back(*itr);
        ++itr;
    }
    uint64_t uinteger = 0;
    uint32_t digitCount = isZeroAtFirst ? 1 : 0;
    bool isOverflow = false;
    while ('0' <= *itr && *itr <= '9') {
        if (isZeroAtFirst) {
            return this->fail("Unexpected '0' character is found while parsing number.");
        }
        str.push_back(*itr);
        ++digitCount;
        if (isOverflow || (uinteger >= 922337203685477580ULL && int(*itr - '0') > 7)) {
            isOverflow = true;
        } else {
            uinteger = uinteger * 10 + static_cast<int32_t>(*itr - '0');
        }
        ++itr;
    }
    if (digitCount == 0) {
        return this->fail("Digit is not found while parsing number.");
    }

    uint32_t fracLength = 0;
    if (*itr == '.') {
        str.push_back(*itr);
        ++itr;
        while ('0' <= *itr && *itr <= '9') {
            str.push_back(*itr);
            ++fracLength;
            ++itr;
        }
        if (fracLength == 0) {
            return this->fail("Digit is not found after the decimal point while parsing number.");
        }
    }

    int32_t exp = 0;
    if (*itr == 'e' || *itr == 'E') {
        str.push_back('e');
        bool isNegativeExp = false;
        ++itr;
        if (*itr == '+') {
            ++itr;
        } else if (*itr == '-') {
            str.push_back(*itr);
            isNegativeExp = true;
            ++itr;
        }
        digitCount = 0;
        isZeroAtFirst = *itr == '0';
        if (isZeroAtFirst) {
            ++itr;
            str.erase(str.size() - 1);
            if (isNegativeExp) { str.erase(str.size() - 1); }
        }
        while ('0' <= *itr && *itr <= '9') {
            if (isZeroAtFirst) {
                return this->fail("Unexpected '0' character is found while parsing number.");
            }
            ++digitCount;
            str.push_back(*itr);
            exp = exp * 10 + static_cast<int32_t>(*itr - '0');
            ++itr;
        }
        if (!isZeroAtFirst && digitCount == 0) {
            return this->fail("Digit is not found after exponent keyword while parsing number.");
        }
        if (isNegativeExp) { exp = -exp; }
    }

    if (fracLength == 0 && exp == 0 && !isOverflow) {
        const int64_t v = static_cast<int64_t>(isNegative ? -uinteger : uinteger);
        if (value) {
            value->setInteger(v);
        } else if (handler && !handler->onInteger(v)) {
            return this->fail("SAX handler cancels parsing.");
        }
    } else {
        char* endp = 0;
        const double f64 = strtod(str.c_str(), &endp);
        if (endp == str.c_str() + str.size()) {
            if (value) {
                value->setFloat(f64);
            } else if (handler && !handler->onFloat(f64)) {
                return this->fail("SAX handler cancels parsing.");
            }
        } else {
            return this->fail("Failed to parse floating point.");
        }
    }
    return true;
}
template<typename Iter>
inline bool Parser::parse_string(Value* value, AbstractParseHandler* handler, Iter& itr, const Iter& end) {
    String str;
    if (this->parse_string(str, itr, end)) {
        if (value) {
            value->setString(str);
        } else if (handler && !handler->onString(str)) {
            return this->fail("SAX handler cancels parsing.");
        }
        return true;
    } else {
        return false;
    }
}
template<typename Iter>
inline bool Parser::parse_hex(uint16_t& hex, Iter& itr, const Iter& end) {
    for (int16_t i = 12; i >= 0; i -= 4) {
        if (itr == end) { return false; }
        if ('0' <= *itr && *itr <= '9') {
            hex |= uint16_t(*itr - '0') << i;
        } else if ('a' <= *itr && *itr <= 'f') {
            hex |= uint16_t(*itr - 'a' + 0xa) << i;
        } else if ('A' <= *itr && *itr <= 'F') {
            hex |= uint16_t(*itr - 'A' + 0xa) << i;
        } else {
            return this->fail("Invalid unicode hex string is found while parsing string.");
        }
        if (i > 0) { ++itr; }
    }
    return true;
}
template<typename Iter>
inline bool Parser::parse_unicode(String& str, Iter& itr, const Iter& end) {
    uint16_t u1 = 0;
    uint16_t u2 = 0;
    if (!this->parse_hex(u1, ++itr, end)) { return false; }
    if (0xd800 <= u1 && u1 <= 0xdfff) {
        if (0xdc00 <= u1) { return false; }
        // Surrogate pair
        if (*(++itr) != '\\' || *(++itr) != 'u') {
            return this->fail("Invalid unicode surrogate pair is found while parsing string.");
        }
        if (!this->parse_hex(u2, ++itr, end)) { return false; }
        if (u2 < 0xdc00 || 0xdfff < u2) {
            return this->fail("Invalid unicode surrogate pair is found while parsing string.");
        }
    }
    CodePoint cp(u1, u2);
    cp.toUtf8(str);
    return true;
}
template<typename Iter>
inline bool Parser::parse_string(String& str, Iter& itr, const Iter& end) {
    while (++itr != end) {
        if (*itr == '"') {
            ++itr;
            return true;
        } else if (*itr == '\\') {
            ++itr;
            switch (*itr) {
            case '"': str.push_back('"'); break;
            case '/': str.push_back('/'); break;
            case '\\': str.push_back('\\'); break;
            case 'b': str.push_back('\b'); break;
            case 'f': str.push_back('\f'); break;
            case 'n': str.push_back('\n'); break;
            case 'r': str.push_back('\r'); break;
            case 't': str.push_back('\t'); break;
            case 'u': if (!this->parse_unicode(str, itr, end)) { return false; } break;
            default:
                return this->fail("Unexpected escape character is found while parsing string.");
            }
        } else {
            str.push_back(*itr);
        }
    }
    return this->fail("Expected string ending character '\"' is not found.");
}
template<typename Iter>
inline bool Parser::parse_array(Value* value, AbstractParseHandler* handler, Iter& itr, const Iter& end, const ParseOptions& options) {
    size_t count = 0;
    if (value) {
        value->setType(kArray);
    } else if (handler && !handler->beginArray()) {
        return this->fail("SAX handler cancels parsing.");
    }
    while (++itr != end) {
        this->skip_white_space(itr, end);
        if (*itr == ']') {
            if (count == 0 || (options & kParseOptionAllowCommaEnding)) {
                if (handler && !handler->endArray(count)) {
                    return this->fail("SAX handler cancels parsing.");
                }
                ++itr;
                break;
            } else {
                return this->fail("Unexpected comma exists while parsing array.");
            }
            break;
        } else {
            bool ok = false;
            if (value) {
                Value newValue;
                ok = this->parse_value(&newValue, handler, itr, end, options);
                value->push_back(newValue);
            } else {
                ok = this->parse_value(0, handler, itr, end, options);
            }
            if (!ok) { return false; }
            ++count;

            this->skip_white_space(itr, end);
            if (*itr == ',') {
                continue;
            } else if (*itr == ']') {
                if (handler && !handler->endArray(count)) {
                    return this->fail("SAX handler cancels parsing.");
                }
                ++itr;
                break;
            } else {
                return this->fail("Unexpected string exists while parsing array.");
            }
        }
    }
    return true;
}
template<typename Iter>
inline bool Parser::parse_object(Value* value, AbstractParseHandler* handler, Iter& itr, const Iter& end, const ParseOptions& options) {
    size_t count = 0;
    if (value) {
        value->setType(kObject);
    } else if (handler && !handler->beginObject()) {
        return this->fail("SAX handler cancels parsing.");
    }
    while (++itr != end) {
        this->skip_white_space(itr, end);
        if (*itr == '"') {
            String key;
            if (!this->parse_string(key, itr, end)) {
                return false;
            }
            if (handler && !handler->onObjectKey(key)) {
                return this->fail("SAX handler cancels parsing.");
            }

            this->skip_white_space(itr, end);
            if (*itr == ':') {
                ++itr;
                bool ok = false;
                if (value) {
                    Value newValue;
                    ok = this->parse_value(&newValue, handler, itr, end, options);
                    value->insert(key, newValue);
                } else {
                    ok = this->parse_value(0, handler, itr, end, options);
                }
                if (!ok) { return false; }
                ++count;

                this->skip_white_space(itr, end);
                if (*itr == ',') {
                    continue;
                } else if (*itr == '}') {
                    if (handler && !handler->endObject(count)) {
                        return this->fail("SAX handler cancels parsing.");
                    }
                    ++itr;
                    break;
                } else {
                    return this->fail("Unexpected string exists while parsing object.");
                }
            } else {
                return this->fail("Unexpected string exists while parsing object.");
            }
        } else if (*itr == '}') {
            if (count == 0 || (options & kParseOptionAllowCommaEnding)) {
                if (handler && !handler->endObject(count)) {
                    return this->fail("SAX handler cancels parsing.");
                }
                ++itr;
                break;
            } else {
                return this->fail("Unexpected comma exists while parsing object.");
            }
        }
    }
    return true;
}

template<typename CharType> inline bool Parser::is_white_space(const CharType& c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}
template<typename Iter> inline void Parser::skip_white_space(Iter& itr, const Iter& end) {
    while (is_white_space(*itr) && itr != end) {
        ++itr;
    }
}
template<typename Iter> inline void Parser::skip_utf8_bom(Iter& itr, const Iter& end) {
    if (*itr == 0xef && *(++itr) == 0xbb && *(++itr) == 0xbf) {
        ++itr;
    }
}
inline bool Parser::fail(const String& error) {
    lastError_ = error;
    return false;
}

/**
 * Serializer class implementation.
 */
template<typename StringType>
inline bool Serializer::serialize(StringType& str, const Value& value, const SerializeOptions& options, String* errorMessage) const {
    Attributes attr;
    attr.pretty = options & kSerializeOptionPretty;
    if (attr.pretty) {
        switch (options & kSerializeOptionTabMask) {
        case kSerializeOption4Spaces: attr.tab = "    "; break;
        case kSerializeOptionTab: attr.tab = "\t"; break;
        default: attr.tab = "  "; break;
        }
        attr.lineBreak = (options & kSerializeOptionLineBreakCRLF) ? "\r\n" : "\n";
    }
    return this->serialize(str, value, attr, attr.pretty ? 0 : -1, errorMessage);
}

template<typename StringType>
inline StringType& Serializer::int64ToString(StringType& str, const int64_t& value) {
    char buf[128] = {0};
#ifdef _MSC_VER
    const auto s = _snprintf_s(buf, 127, _TRUNCATE, "%lld", value);
#else
    const auto s = snprintf(buf, 127, "%lld", value);
#endif
    for (int i = 0; i < s; ++i) {
        str.push_back(buf[i]);
    }
    return str;
}
inline String Serializer::int64ToString(const int64_t& value) {
    String str; return Serializer::int64ToString(str, value);
}

template<typename StringType>
inline bool Serializer::serialize(StringType& str, const Value& value, const Attributes& attr, const int32_t& indentLevel, String* errorMessage) const {
    switch (value.type()) {
    case kNull: this->append(str, "null"); break;
    case kBoolean:
    case kInteger:
        this->append(str, value.toString()); break;
    case kFloat: {
        Double d(value.as<double>());
        if (d.isNanOrInf()) {
            if (errorMessage) { *errorMessage = "Floating point is nan or inf."; }
            return false;
        }
        this->append(str, value.toString()); break;
        break;
    }
    case kString: {
        this->serialize_string(str, value.as<String>());
        break;
    }
    case kObject: {
        auto indent = indentLevel;
        str.push_back('{');
        if (indent > -1) {
            ++indent;
        }
        const auto& object = value.as<Object>();
        for (auto itr = object.begin(); itr != object.end(); ++itr) {
            if (itr != object.begin()) { str.push_back(','); }
            if (indent > -1) {
                this->indent(str, attr, indent);
            }
            this->serialize_string(str, itr->first);
            str.push_back(':');
            if (attr.pretty) { str.push_back(' '); }
            if (!this->serialize(str, itr->second, attr, indent, errorMessage)) {
                return false;
            }
        }
        if (indent > -1) {
            --indent;
            if (!object.empty()) {
                this->indent(str, attr, indent);
            }
        }
        str.push_back('}');
        break;
    }
    case kArray: {
        auto indent = indentLevel;
        str.push_back('[');
        if (indent > -1) {
            ++indent;
        }
        const auto& array = value.as<Array>();
        for (size_t i = 0; i < array.size(); ++i) {
            if (i > 0) { str.push_back(','); }
            if (indent > -1) {
                this->indent(str, attr, indent);
            }
            if (!this->serialize(str, array[i], attr, indent, errorMessage)) {
                return false;
            }
        }
        if (indent > -1) {
            --indent;
            if (!array.empty()) {
                this->indent(str, attr, indent);
            }
        }
        str.push_back(']');
        break;
    }
    default: break;
    }
    return true;
}

template<typename StringType>
inline void Serializer::serialize_string(StringType& str, const String& value) const {
    static char kHexDigits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    static const char kEscape[] = {
        'u', 'u', 'u', 'u', 'u', 'u', 'u', 'u', 'b', 't', 'n', 'u', 'f', 'r', 'u', 'u', // 00
        'u', 'u', 'u', 'u', 'u', 'u', 'u', 'u', 'u', 'u', 'u', 'u', 'u', 'u', 'u', 'u', // 10
          0,   0, '"',   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 20
          0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 30
          0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 40
          0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,'\\',   0,   0,   0, // 50
          0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 60
          0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 'u', // 70
          0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 80
          0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 90
          0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // a0
          0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // b0
          0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // c0
          0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // d0
          0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // e0
          0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0  // f0
    };
    str.push_back('"');
    for (size_t i = 0; i < value.size(); ++i) {
        const char ch = kEscape[static_cast<uint8_t>(value[i])];
        if (ch == 0) {
            str.push_back(value[i]);
        } else {
            str.push_back('\\');
            str.push_back(ch);
            if (ch == 'u') {
                str.push_back('0');
                str.push_back('0');
                str.push_back(kHexDigits[(value[i] >> 4) & 0xf]);
                str.push_back(kHexDigits[value[i] & 0xf]);
            }
        }
    }
    str.push_back('"');
}

template<typename StringType>
inline void Serializer::indent(StringType& str, const Attributes& attr, const int32_t& indent) const {
    if (attr.pretty) {
        this->append(str, attr.lineBreak);
        for (int32_t i = 0; i < indent; ++i) {
            this->append(str, attr.tab);
        }
    }
}
template<typename StringType>
inline void Serializer::append(StringType& str, const String& app) const {
    for (size_t i = 0; i < app.size(); ++i) {
        str.push_back(app[i]);
    }
}

} // namespace pocketjson

#endif // POCKETJSON_H
