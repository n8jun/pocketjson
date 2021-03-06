/**
 * pocketjson
 * Copyright (c) 2016 Jun Nishimura.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef POCKETJSON_H
#define POCKETJSON_H

#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <locale.h>
#include <string>
#include <vector>
#include <iterator>
#include <map>
#include <iostream>
#include <algorithm>
#include <utility>

#ifdef _MSC_VER
#if _MSC_VER >= 1600
#define _POCKETJSON_HAS_RVALUE_REFERENCES
#endif
#endif

#if defined(__has_feature)
#if __has_feature(cxx_rvalue_references)
#define _POCKETJSON_HAS_RVALUE_REFERENCES
#endif
#endif

#if defined(__GXX_EXPERIMENTAL_CXX0X__)
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

enum ParseOption {
    kParseOptionNone = 0x00,
    kParseOptionAllowCommaEnding = 0x01,
    kParseOptionAllowGabage = 0x02,
    kParseOptionAllowLooseFormat = kParseOptionAllowCommaEnding | kParseOptionAllowGabage
}; // ParseOption enum

enum SerializeOption {
    kSerializeOptionNone = 0x00,
    kSerializeOption4Spaces = 0x01,
    kSerializeOptionTab = 0x02,
    kSerializeOptionCRLF = 0x04,
    kSerializeOptionPretty = 0x80,
    kSerializeOptionPretty4Spaces = kSerializeOptionPretty | kSerializeOption4Spaces,
    kSerializeOptionPrettyTab = kSerializeOptionPretty | kSerializeOptionTab,
    kSerializeOptionPrettyCRLF = kSerializeOptionPretty | kSerializeOptionCRLF,
    kSerializeOptionPretty4SpacesCRLF = kSerializeOptionPretty | kSerializeOption4Spaces | kSerializeOptionCRLF,
    kSerializeOptionPrettyTabCRLF = kSerializeOptionPretty | kSerializeOptionTab | kSerializeOptionCRLF
}; // SerializeOption enum

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

    bool operator ==(const Value& rhs) const;
    bool operator !=(const Value& rhs) const;

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
    void setNull();
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
    template<typename T> void setEnum(const T& v);

public:
    template<typename Iter> bool serialize(const Iter& itr, const SerializeOption& options = kSerializeOptionNone, String* errorMessage = 0) const;
    bool serialize(String& str, const SerializeOption& options = kSerializeOptionNone, String* errorMessage = 0) const;
    String serialize(const SerializeOption& options = kSerializeOptionNone, String* errorMessage = 0) const;

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
    template<typename T> T toEnum(const T& defaults = T(0)) const;

    bool empty() const;
    size_t size() const;
    bool contains(const String& key) const;
    bool contains(const size_t& index) const;

    void swap(Value& v);

    template<typename T> bool is() const;
    template<typename T> T& as();
    template<typename T> const T& as() const;

private:
    static const Value& s_null();
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

template<typename Iter> inline Value parse(const Iter& begin, const Iter& end, const ParseOption& options = kParseOptionNone, String* errorMessage = 0);
inline Value parse(const String& str, const ParseOption& options = kParseOptionNone, String* errorMessage = 0);
template<typename Iter> inline bool parse(Value& value, const Iter& begin, const Iter& end, const ParseOption& options = kParseOptionNone, String* errorMessage = 0);
inline bool parse(Value& value, const String& str, const ParseOption& options = kParseOptionNone, String* errorMessage = 0);
template<typename Iter> inline bool parse(AbstractParseHandler* handler, const Iter& begin, const Iter& end, const ParseOption& options = kParseOptionNone, String* errorMessage = 0);
inline bool parse(AbstractParseHandler* handler, const String& str, const ParseOption& options = kParseOptionNone, String* errorMessage = 0);


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
    template<typename Iter> bool parse(Value& value, const Iter& begin, const Iter& end, const ParseOption& options = kParseOptionNone, String* errorMessage = 0);
    template<typename Iter> bool parse(AbstractParseHandler* handler, const Iter& begin, const Iter& end, const ParseOption& options = kParseOptionNone, String* errorMessage = 0);

private:
    template<typename Iter> bool parse(Value* value, AbstractParseHandler* handler, const Iter& begin, const Iter& end, const ParseOption& options = kParseOptionNone, String* errorMessage = 0);

    template<typename Iter> bool parse_value(Value* value, AbstractParseHandler* handler, Iter& itr, const ParseOption& options);
    template<typename Iter> bool parse_number(Value* value, AbstractParseHandler* handler, Iter& itr);
    template<typename Iter> bool parse_string(Value* value, AbstractParseHandler* handler, Iter& itr);
    template<typename Iter> bool parse_hex(uint16_t& hex, Iter& itr);
    template<typename Iter> bool parse_unicode(String& str, Iter& itr);
    template<typename Iter> bool parse_string(String& str, Iter& itr);
    template<typename Iter> bool parse_array(Value* value, AbstractParseHandler* handler, Iter& itr, const ParseOption& options);
    template<typename Iter> bool parse_object(Value* value, AbstractParseHandler* handler, Iter& itr, const ParseOption& options);
    template<typename CharType> bool is_white_space(const CharType& c);
    template<typename Iter> void skip_white_space(Iter& itr);
    template<typename Iter> void skip_utf8_bom(Iter& itr);

    bool fail(const String& error);

private:
    String lastError_;

    template<typename Iter> class Iterator {
    private:
        Iter itr_;
        Iter end_;
    public:
        inline Iterator(const Iter& itr, const Iter& end): itr_(itr), end_(end) {}
        inline ~Iterator() {}
    public:
        inline Iterator& operator ++() { ++itr_; return *this; }
        inline operator bool() const { return itr_ != end_; }
        inline typename Iter::value_type operator *() const { return itr_ == end_ ? 0 : *itr_; }
    }; // Iterator class

}; // Parser class

class Serializer {
public:
    inline Serializer() {}
    inline ~Serializer() {}

public:
    template<typename Iter> bool serialize(const Iter& itr, const Value& value, const SerializeOption& options = kSerializeOptionNone, String* errorMessage = 0);

public:
    template<typename Iter> static void int64ToString(Iter itr, const int64_t& value);
    static String int64ToString(const int64_t& value);

private:
    struct Attributes {
        bool pretty;
        String tab;
        String lineBreak;
    }; // Attributes struct

    template<typename Iter> bool serialize(Iter& itr, const Value& value, const Attributes& attr, const int& indentLevel, String* errorMessage = 0);
    template<typename Iter> void serialize_string(Iter& itr, const String& value);
    template<typename Iter> void indent(Iter& itr, const Attributes& attr, const int& indent);
    template<typename Iter> void append(Iter& itr, const String& app);

}; // Serializer class

class Double {
public:
    inline Double(): u_(0) {}
    inline Double(const double& d): d_(d) {}
    inline Double(const uint64_t& u): u_(u) {}
    inline ~Double() {}

public:
    inline int sign() const { return isMinus() ? -1 : 1; }
    inline uint64_t significand() const { return u_ & kSignificandMask; }
    inline int exponent() const { return static_cast<int>((u_ & kExponentMask) >> kSignificandBitSize) - kExponentBias; }

    inline bool isMinus() const { return u_ & kSignMask ? true : false; }
    inline bool isZero() const { return (u_ & (kExponentMask | kSignificandMask)) == 0; }
    inline bool isNan() const { return isNanOrInf() && significand() != 0; }
    inline bool isInf() const { return isNanOrInf() && significand() == 0; }
    inline bool isNanOrInf() const { return (u_ & kExponentMask) == kExponentMask; }

public:
    static const uint64_t kSignMask = 0x8000000000000000;
    static const uint64_t kExponentMask = 0x7ff0000000000000;
    static const uint64_t kSignificandMask = 0x000fffffffffffff;
    static const int kSignificandBitSize = 52;
    static const int kExponentBias = 0x3ff;

    static inline double strToDouble(const char* str, bool* success) {
        String tmp = str;
        const char* decimal = ::localeconv()->decimal_point;
        const size_t pos = tmp.find('.');
        if (pos != String::npos) {
            tmp.replace(pos, 1, 1, decimal[0]);
        }

        char* endp = 0;
        const double result = strtod(tmp.c_str(), &endp);
        *success = (endp == tmp.c_str() + tmp.size());
        return result;
    }

    template<typename Iter>
    inline bool toString(Iter itr) const {
        if (isZero()) {
            *itr++ = '0'; *itr++ = '.'; *itr++ = '0';
            return true;
        } else if (isNan()) {
            *itr++ = 'n'; *itr++ = 'a'; *itr++ = 'n';
            return false;
        } else if (isInf()) {
            if (isMinus()) { *itr++ = '-'; }
            *itr++ = 'i'; *itr++ = 'n'; *itr++ = 'f';
            return false;
        } else {
            char buf[128] = {0};
            const char* decimal = ::localeconv()->decimal_point;
#ifdef _MSC_VER
            const int s = _snprintf_s(buf, 127, _TRUNCATE, "%.17g", d_);
#else
            const int s = snprintf(buf, 127, "%.17g", d_);
#endif
            for (int i = 0; i < s; ++i) {
                if (buf[i] == decimal[0]) {
                    *itr++ = '.';
                } else {
                    *itr++ = buf[i];
                }
            }
            return true;
        }
    }
    inline String toString() const {
        String s; this->toString(std::back_inserter(s)); return s;
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
    template<typename Iter>
    inline void toUtf8(Iter itr) const {
        if (value_ < 0x80) {
            this->to7BitUtf8(itr);
        } else if (value_ < 0x0800) {
            this->to11BitUtf8(itr);
        } else if (value_ < 0x010000) {
            this->to16BitUtf8(itr);
        } else {
            this->to21BitUtf8(itr);
        }
    }

private:
    template<typename Iter> inline void to7BitUtf8(Iter& itr) const {
        *itr++ = bytes_[0];
    }
    template<typename Iter> inline void to11BitUtf8(Iter& itr) const {
        *itr++ = 0xc0 | (value_ >> 6);
        *itr++ = 0x80 | (bytes_[0] & 0x3f);
    }
    template<typename Iter> inline void to16BitUtf8(Iter& itr) const {
        *itr++ = 0xe0 | (value_ >> 12);
        *itr++ = 0x80 | ((value_ >> 6) & 0x3f);
        *itr++ = 0x80 | (bytes_[0] & 0x3f);
    }
    template<typename Iter> inline void to21BitUtf8(Iter& itr) const {
        *itr++ = 0xf0 | (value_ >> 18);
        *itr++ = 0x80 | ((value_ >> 12) & 0x3f);
        *itr++ = 0x80 | ((value_ >> 6) & 0x3f);
        *itr++ = 0x80 | (bytes_[0] & 0x3f);
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
    inline const uint32_t& count() const { return referenceCount_; }
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

inline bool Value::operator ==(const Value& rhs) const {
    if (type_ != rhs.type_) { return false; }
    switch (type_) {
    case kNull: return true;
    case kBoolean: return boolean_ == rhs.boolean_;
    case kInteger: return integer_ == rhs.integer_;
    case kFloat: return float_ == rhs.float_;
    case kString: return container_->data<String>() == rhs.container_->data<String>();
    case kArray: return container_->data<Array>() == rhs.container_->data<Array>();
    case kObject: return container_->data<Object>() == rhs.container_->data<Object>();
    default: break;
    }
    return false;
}
inline bool Value::operator !=(const Value& rhs) const {
    return !(*this == rhs);
}

#ifdef _POCKETJSON_HAS_RVALUE_REFERENCES
inline Value::Value(Value&& v): type_(v.type_), integer_(v.integer_) { v.integer_ = 0; }
inline Value& Value::operator =(Value&& rhs) {
    if (this != &rhs) {
        std::swap(type_, rhs.type_);
        std::swap(integer_, rhs.integer_);
    }
    return *this;
}
#endif

inline Value& Value::operator [](const String& key) {
    this->setType(kObject);
    if (container_->count() > 1) {
        this->release();
        container_ = new Container<Object>(container_->data<Object>());
    }
    return container_->data<Object>()[key];
}
inline const Value& Value::operator [](const String& key) const {
    if (this->isObject()) {
        const Object& object = container_->data<Object>();
        const Object::const_iterator itr = object.find(key);
        return itr != object.end() ? itr->second : Value::s_null();
    } else {
        return Value::s_null();
    }
}
inline Value& Value::operator [](const size_t& index) {
    this->setType(kArray);
    if (container_->count() > 1) {
        this->release();
        container_ = new Container<Array>(container_->data<Array>());
    }
    Array& array = container_->data<Array>();
    if (index >= array.size()) {
        array.resize(index + 1);
    }
    return array[index];
}
inline const Value& Value::operator [](const size_t& index) const {
    if (this->isArray()) {
        Array& array = container_->data<Array>();
        return index < array.size() ? array[index] : Value::s_null();
    } else {
        return Value::s_null();
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
    switch (type_) {
    case kString: container_->data<String>().clear(); break;
    case kObject: container_->data<Object>().clear(); break;
    case kArray: container_->data<Array>().clear(); break;
    default: integer_ = 0; break;
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
inline void Value::setNull() {
    if (type_ != kNull) {
        this->release();
        type_ = kNull;
        integer_ = 0;
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
#define _POCKETJSON_SET_CONAINER_IMPL(type, classType) if (type_ == type && container_->count() <= 1) { container_->data<classType>() = v; } else { this->release(); type_ = type; container_ = new Container<classType>(v); }
inline void Value::setString(const String& v) { _POCKETJSON_SET_CONAINER_IMPL(kString, String); }
inline void Value::setArray(const Array& v) { _POCKETJSON_SET_CONAINER_IMPL(kArray, Array); }
inline void Value::setObject(const Object& v) { _POCKETJSON_SET_CONAINER_IMPL(kObject, Object); }
#undef JSON_SET_CONAINER_IMPL
template<typename T> inline void Value::setEnum(const T& v) { this->setInteger(static_cast<unsigned int>(v)); }

template<typename Iter> inline bool Value::serialize(const Iter& itr, const SerializeOption& options, String* errorMessage) const {
    Serializer s; return s.serialize(itr, *this, options, errorMessage);
}
inline bool Value::serialize(String& str, const SerializeOption& options, String* errorMessage) const {
    return this->serialize(std::back_inserter(str), options, errorMessage);
}
inline String Value::serialize(const SerializeOption& options, String* errorMessage) const {
    String s; this->serialize(std::back_inserter(s), options, errorMessage); return s;
}

inline const Type& Value::type() const { return type_; }
inline bool Value::isNull() const { return type_ == kNull; }
inline bool Value::isBoolean() const { return type_ == kBoolean; }
inline bool Value::isInteger() const { return type_ == kInteger; }
inline bool Value::isFloat() const { return type_ == kFloat; }
inline bool Value::isNumber() const { return type_ & kNumber ? true : false; }
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
#if defined(_MSC_VER) && _MSC_VER < 1800
inline double round(const double& v) {
    return v < 0.0 ? ceil(v - 0.5) : floor(v + 0.5);
}
inline long long strtoll(const char* nptr, char** endptr, int base) {
    return _strtoi64(nptr, endptr, base);
}
#endif

inline bool is_range(const int64_t& value, const int64_t& minValue, const int64_t& maxValue) {
    return minValue <= value && value <= maxValue;
}
template<typename T> inline T double_to_value(const double& value, const double& minValue, const double& maxValue, const T& defaults) {
    const double d = round(value);
    return minValue <= d && d <= maxValue ? static_cast<T>(d) : defaults;
}
template<typename T> inline T llstr_to_value(const String& str, const T& minValue, const T& maxValue, const T& defaults) {
    char* endp = 0;
    const long long value = strtoll(str.c_str(), &endp, 0);
    return endp == str.c_str() + str.size() && is_range(value, minValue, maxValue) ? static_cast<T>(value) : defaults;
}

inline char Value::toChar(const char& defaults) const {
    switch (type_) {
    case kInteger: return is_range(integer_, CHAR_MIN, CHAR_MAX) ? static_cast<char>(integer_) : defaults;
    case kFloat: return double_to_value<char>(float_, static_cast<double>(CHAR_MIN), static_cast<double>(CHAR_MAX), defaults);
    case kBoolean: return boolean_ ? 1 : 0;
    case kString: return llstr_to_value<char>(container_->data<String>(), CHAR_MIN, CHAR_MAX, defaults);
    default: break;
    }
    return defaults;
}
inline short Value::toShort(const short& defaults) const {
    switch (type_) {
    case kInteger: return is_range(integer_, SHRT_MIN, SHRT_MAX) ? static_cast<short>(integer_) : defaults;
    case kFloat: return double_to_value<short>(float_, static_cast<double>(SHRT_MIN), static_cast<double>(SHRT_MAX), defaults);
    case kBoolean: return boolean_ ? 1 : 0;
    case kString: return llstr_to_value<short>(container_->data<String>(), SHRT_MIN, SHRT_MAX, defaults);
    default: break;
    }
    return defaults;
}
inline int Value::toInt(const int& defaults) const {
    switch (type_) {
    case kInteger: return is_range(integer_, INT_MIN, INT_MAX) ? static_cast<int>(integer_) : defaults;
    case kFloat: return double_to_value<int>(float_, static_cast<double>(INT_MIN), static_cast<double>(INT_MAX), defaults);
    case kBoolean: return boolean_ ? 1 : 0;
    case kString: return llstr_to_value<int>(container_->data<String>(), INT_MIN, INT_MAX, defaults);
    default: break;
    }
    return defaults;
}
inline long Value::toLong(const long& defaults) const {
    switch (type_) {
    case kInteger: return is_range(integer_, LONG_MIN, LONG_MAX) ? static_cast<long>(integer_) : defaults;
    case kFloat: return double_to_value<long>(float_, static_cast<double>(LONG_MIN), static_cast<double>(LONG_MAX), defaults);
    case kBoolean: return boolean_ ? 1 : 0;
    case kString: return llstr_to_value<long>(container_->data<String>(), LONG_MIN, LONG_MAX, defaults);
    default: break;
    }
    return defaults;
}
inline long long Value::toLLong(const long long& defaults) const {
    switch (type_) {
    case kInteger: return static_cast<long long>(integer_);
    case kFloat: return double_to_value<long long>(float_, static_cast<double>(LLONG_MIN), static_cast<double>(LLONG_MAX), defaults);
    case kBoolean: return boolean_ ? 1 : 0;
    case kString: return llstr_to_value<long long>(container_->data<String>(), LLONG_MIN, LLONG_MAX, defaults);
    default: break;
    }
    return defaults;
}
inline unsigned char Value::toUChar(const unsigned char& defaults) const {
    switch (type_) {
    case kInteger: return is_range(integer_, 0, UCHAR_MAX) ? static_cast<unsigned char>(integer_) : defaults;
    case kFloat: return double_to_value<unsigned char>(float_, 0, static_cast<double>(UCHAR_MAX), defaults);
    case kBoolean: return boolean_ ? 1 : 0;
    case kString: return llstr_to_value<unsigned char>(container_->data<String>(), 0, UCHAR_MAX, defaults);
    default: break;
    }
    return defaults;
}
inline unsigned short Value::toUShort(const unsigned short& defaults) const {
    switch (type_) {
    case kInteger: return is_range(integer_, 0, USHRT_MAX) ? static_cast<unsigned short>(integer_) : defaults;
    case kFloat: return double_to_value<unsigned short>(float_, 0, static_cast<double>(USHRT_MAX), defaults);
    case kBoolean: return boolean_ ? 1 : 0;
    case kString: return llstr_to_value<unsigned short>(container_->data<String>(), 0, USHRT_MAX, defaults);
    default: break;
    }
    return defaults;
}
inline unsigned int Value::toUInt(const unsigned int& defaults) const {
    switch (type_) {
    case kInteger: return is_range(integer_, 0, UINT_MAX) ? static_cast<unsigned int>(integer_) : defaults;
    case kFloat: return double_to_value<unsigned int>(float_, 0, static_cast<double>(UINT_MAX), defaults);
    case kBoolean: return boolean_ ? 1 : 0;
    case kString: return llstr_to_value<unsigned int>(container_->data<String>(), 0, UINT_MAX, defaults);
    default: break;
    }
    return defaults;
}
inline unsigned long Value::toULong(const unsigned long& defaults) const {
    switch (type_) {
    case kInteger: return integer_ > 0 ? static_cast<unsigned long>(integer_) : defaults;
    case kFloat: return double_to_value<unsigned long>(float_, 0, static_cast<double>((ULONG_MAX == ULLONG_MAX) ? LLONG_MAX : ULONG_MAX), defaults);
    case kBoolean: return boolean_ ? 1 : 0;
    case kString: return llstr_to_value<unsigned long>(container_->data<String>(), 0, (ULONG_MAX == ULLONG_MAX) ? LLONG_MAX : ULONG_MAX, defaults);
    default: break;
    }
    return defaults;
}
inline unsigned long long Value::toULLong(const unsigned long long& defaults) const {
    switch (type_) {
    case kInteger: return integer_ > 0 ? static_cast<unsigned long long>(integer_) : defaults;
    case kFloat: return double_to_value<unsigned long long>(float_, 0, static_cast<double>(LLONG_MAX), defaults);
    case kBoolean: return boolean_ ? 1 : 0;
    case kString: return llstr_to_value<unsigned long long>(container_->data<String>(), 0, LLONG_MAX, defaults);
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
        const String& str = container_->data<String>();
        bool ok = false;
        const float value = static_cast<float>(Double::strToDouble(str.c_str(), &ok));
        return ok ? value : defaults;
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
        const String& str = container_->data<String>();
        bool ok = false;
        const double value = Double::strToDouble(str.c_str(), &ok);
        return ok ? value : defaults;
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
template<typename T> inline T Value::toEnum(const T& defaults) const {
    return static_cast<T>(this->toLLong(static_cast<long long>(defaults)));
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
        const Object& object = container_->data<Object>();
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

inline void Value::swap(Value& v) {
    std::swap(type_, v.type_);
    std::swap(integer_, v.integer_);
}

template<> inline bool Value::is<bool>() const { return this->isBoolean(); }
template<> inline bool Value::is<int64_t>() const { return this->isInteger(); }
template<> inline bool Value::is<double>() const { return this->isFloat(); }
template<> inline bool Value::is<String>() const { return this->isString(); }
template<> inline bool Value::is<Array>() const { return this->isArray(); }
template<> inline bool Value::is<Object>() const { return this->isObject(); }

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

inline const Value& Value::s_null() { static Value null; return null; }
inline void Value::release() {
    if ((type_ & kContainer) && container_ && container_->decrement()) {
        delete container_;
        container_ = 0;
    }
}

inline std::istream& operator >>(std::istream& is, Value& v) {
    std::istreambuf_iterator<char> itr(is.rdbuf());
    std::istreambuf_iterator<char> end;
    if (!parse(v, itr, end)) {
        is.setstate(std::ios::failbit);
    }
    return is;
}
inline std::ostream& operator <<(std::ostream& os, const Value& v) {
    v.serialize(std::ostream_iterator<char>(os));
    return os;
}

template<typename Iter> inline Value parse(const Iter& begin, const Iter& end, const ParseOption& options, String* errorMessage) {
    Parser parser;
    Value value;
    parser.parse(value, begin, end, options, errorMessage);
    return value;
}
inline Value parse(const String& str, const ParseOption& options, String* errorMessage) {
    return parse(str.begin(), str.end(), options, errorMessage);
}
template<typename Iter> inline bool parse(Value& value, const Iter& begin, const Iter& end, const ParseOption& options, String* errorMessage) {
    Parser parser;
    return parser.parse(value, begin, end, options, errorMessage);
}
inline bool parse(Value& value, const String& str, const ParseOption& options, String* errorMessage) {
    return parse(value, str.begin(), str.end(), options, errorMessage);
}
template<typename Iter> inline bool parse(AbstractParseHandler* handler, const Iter& begin, const Iter& end, const ParseOption& options, String* errorMessage) {
    Parser parser;
    return parser.parse(handler, begin, end, options, errorMessage);
}
inline bool parse(AbstractParseHandler* handler, const String& str, const ParseOption& options, String* errorMessage) {
    return parse(handler, str.begin(), str.end(), options, errorMessage);
}

/**
 * Parser class impelemtation.
 */
template<typename Iter> inline bool Parser::parse(Value& value, const Iter& begin, const Iter& end, const ParseOption& options, String* errorMessage) {
    return this->parse(&value, 0, begin, end, options, errorMessage);
}
template<typename Iter> inline bool Parser::parse(AbstractParseHandler* handler, const Iter& begin, const Iter& end, const ParseOption& options, String* errorMessage) {
    return this->parse(0, handler, begin, end, options, errorMessage);
}

template<typename Iter> inline bool Parser::parse(Value* value, AbstractParseHandler* handler, const Iter& begin, const Iter& end, const ParseOption& options, String* errorMessage) {
    lastError_.clear();
    Iterator<Iter> itr(begin, end);
    this->skip_utf8_bom(itr);
    bool ok = this->parse_value(value, handler, itr, options);
    if (ok) {
        if (!(options & kParseOptionAllowGabage)) {
            this->skip_white_space(itr);
            if (itr && *itr != 0) {
                lastError_ = "Gabage string exists after json string.";
                ok = false;
            }
        }
    }
    if (errorMessage) { *errorMessage = lastError_; }
    return ok;
}

template<typename Iter> inline bool Parser::parse_value(Value* value, AbstractParseHandler* handler, Iter& itr, const ParseOption& options) {
    this->skip_white_space(itr);
    if (*itr == '"') {
        return this->parse_string(value, handler, itr);
    } else if (*itr == '{') {
        return this->parse_object(value, handler, itr, options);
    } else if (*itr == '[') {
        return this->parse_array(value, handler, itr, options);
    } else if (*itr == '-' || ('0' <= *itr && *itr <= '9')) {
        return this->parse_number(value, handler, itr);
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
                value->setNull();
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
template<typename Iter> inline bool Parser::parse_number(Value* value, AbstractParseHandler* handler, Iter& itr) {
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
    int64_t integer = 0;
    uint32_t digitCount = isZeroAtFirst ? 1 : 0;
    bool isOverflow = false;
    while ('0' <= *itr && *itr <= '9') {
        if (isZeroAtFirst) {
            return this->fail("Unexpected '0' character is found while parsing number.");
        }
        str.push_back(*itr);
        ++digitCount;
        if (isOverflow || (integer >= 922337203685477580LL && int(*itr - '0') > 7)) {
            isOverflow = true;
        } else {
            integer = integer * 10 + static_cast<int>(*itr - '0');
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

    int exp = 0;
    bool expExists = false;
    if (*itr == 'e' || *itr == 'E') {
        expExists = true;
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
        while ('0' <= *itr && *itr <= '9') {
            ++digitCount;
            str.push_back(*itr);
            exp = exp * 10 + static_cast<int>(*itr - '0');
            ++itr;
        }
        if (digitCount == 0) {
            return this->fail("Digit is not found after exponent keyword while parsing number.");
        }
        if (isNegativeExp) { exp = -exp; }
    }

    if (fracLength == 0 && exp == 0 && !isOverflow) {
        const int64_t v = isNegative ? -integer : integer;
        if (value) {
            value->setInteger(v);
        } else if (handler && !handler->onInteger(v)) {
            return this->fail("SAX handler cancels parsing.");
        }
    } else {
        if (expExists && exp == 0) { str.erase(str.find('e')); }
        bool ok = false;
        const double f64 = Double::strToDouble(str.c_str(), &ok);
        if (ok) {
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
template<typename Iter> inline bool Parser::parse_string(Value* value, AbstractParseHandler* handler, Iter& itr) {
    String str;
    if (this->parse_string(str, itr)) {
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
template<typename Iter> inline bool Parser::parse_hex(uint16_t& hex, Iter& itr) {
    for (int16_t i = 12; i >= 0; i -= 4) {
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
template<typename Iter> inline bool Parser::parse_unicode(String& str, Iter& itr) {
    uint16_t u1 = 0;
    uint16_t u2 = 0;
    if (!this->parse_hex(u1, ++itr)) { return false; }
    if (0xd800 <= u1 && u1 <= 0xdfff) {
        if (0xdc00 <= u1) { return false; }
        // Surrogate pair
        if (*(++itr) != '\\' || *(++itr) != 'u') {
            return this->fail("Invalid unicode surrogate pair is found while parsing string.");
        }
        if (!this->parse_hex(u2, ++itr)) { return false; }
        if (u2 < 0xdc00 || 0xdfff < u2) {
            return this->fail("Invalid unicode surrogate pair is found while parsing string.");
        }
    }
    CodePoint cp(u1, u2);
    cp.toUtf8(std::back_inserter(str));
    return true;
}
template<typename Iter> inline bool Parser::parse_string(String& str, Iter& itr) {
    while (++itr) {
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
            case 'u': if (!this->parse_unicode(str, itr)) { return false; } break;
            default:
                return this->fail("Unexpected escape character is found while parsing string.");
            }
        } else {
            str.push_back(*itr);
        }
    }
    return this->fail("Expected string ending character '\"' is not found.");
}
template<typename Iter> inline bool Parser::parse_array(Value* value, AbstractParseHandler* handler, Iter& itr, const ParseOption& options) {
    size_t count = 0;
    if (value) {
        value->setType(kArray);
    } else if (handler && !handler->beginArray()) {
        return this->fail("SAX handler cancels parsing.");
    }
    while (++itr) {
        this->skip_white_space(itr);
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
                ok = this->parse_value(&newValue, handler, itr, options);
                value->push_back(newValue);
            } else {
                ok = this->parse_value(0, handler, itr, options);
            }
            if (!ok) { return false; }
            ++count;

            this->skip_white_space(itr);
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
template<typename Iter> inline bool Parser::parse_object(Value* value, AbstractParseHandler* handler, Iter& itr, const ParseOption& options) {
    size_t count = 0;
    if (value) {
        value->setType(kObject);
    } else if (handler && !handler->beginObject()) {
        return this->fail("SAX handler cancels parsing.");
    }
    while (++itr) {
        this->skip_white_space(itr);
        if (*itr == '"') {
            String key;
            if (!this->parse_string(key, itr)) {
                return false;
            }
            if (handler && !handler->onObjectKey(key)) {
                return this->fail("SAX handler cancels parsing.");
            }

            this->skip_white_space(itr);
            if (*itr == ':') {
                ++itr;
                bool ok = false;
                if (value) {
                    Value newValue;
                    ok = this->parse_value(&newValue, handler, itr, options);
                    value->insert(key, newValue);
                } else {
                    ok = this->parse_value(0, handler, itr, options);
                }
                if (!ok) { return false; }
                ++count;

                this->skip_white_space(itr);
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
template<typename Iter> inline void Parser::skip_white_space(Iter& itr) {
    while (itr && is_white_space(*itr)) {
        ++itr;
    }
}
template<typename Iter> inline void Parser::skip_utf8_bom(Iter& itr) {
    if ((unsigned char)(*itr) == 0xef && (unsigned char)(*(++itr)) == 0xbb && (unsigned char)(*(++itr)) == 0xbf) {
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
template<typename Iter> inline bool Serializer::serialize(const Iter& itr, const Value& value, const SerializeOption& options, String* errorMessage) {
    Attributes attr;
    attr.pretty = options & kSerializeOptionPretty ? true : false;
    if (attr.pretty) {
        switch (options & 0x03) {
        case kSerializeOption4Spaces: attr.tab = "    "; break;
        case kSerializeOptionTab: attr.tab = "\t"; break;
        default: attr.tab = "  "; break;
        }
        attr.lineBreak = (options & kSerializeOptionCRLF) ? "\r\n" : "\n";
    }
    Iter tmp = itr;
    return this->serialize(tmp, value, attr, attr.pretty ? 0 : -1, errorMessage);
}

template<typename Iter> inline void Serializer::int64ToString(Iter itr, const int64_t& value) {
    char buf[128] = {0};
#ifdef _MSC_VER
    const int s = _snprintf_s(buf, 127, _TRUNCATE, "%lld", value);
#else
    const int s = snprintf(buf, 127, "%lld", static_cast<long long>(value));
#endif
    for (int i = 0; i < s; ++i) {
        *itr++ = buf[i];
    }
}
inline String Serializer::int64ToString(const int64_t& value) {
    String s; Serializer::int64ToString(std::back_inserter(s), value); return s;
}

template<typename Iter> inline bool Serializer::serialize(Iter& itr, const Value& value, const Attributes& attr, const int& indentLevel, String* errorMessage) {
    switch (value.type()) {
    case kNull: this->append(itr, "null"); break;
    case kBoolean:
    case kInteger:
        this->append(itr, value.toString()); break;
    case kFloat: {
        Double d(value.as<double>());
        if (d.isNanOrInf()) {
            if (errorMessage) { *errorMessage = "Floating point is nan or inf."; }
            return false;
        }
        d.toString(itr); break;
        break;
    }
    case kString: {
        this->serialize_string(itr, value.as<String>());
        break;
    }
    case kObject: {
        int indent = indentLevel;
        *itr++ = '{';
        if (indent > -1) {
            ++indent;
        }
        const Object& object = value.as<Object>();
        for (Object::const_iterator oitr = object.begin(); oitr != object.end(); ++oitr) {
            if (oitr != object.begin()) { *itr++ = ','; }
            if (indent > -1) {
                this->indent(itr, attr, indent);
            }
            this->serialize_string(itr, oitr->first);
            *itr++ = ':';
            if (attr.pretty) { *itr++ = ' '; }
            if (!this->serialize(itr, oitr->second, attr, indent, errorMessage)) {
                return false;
            }
        }
        if (indent > -1) {
            --indent;
            if (!object.empty()) {
                this->indent(itr, attr, indent);
            }
        }
        *itr++ = '}';
        break;
    }
    case kArray: {
        int indent = indentLevel;
        *itr++ = '[';
        if (indent > -1) {
            ++indent;
        }
        const Array& array = value.as<Array>();
        for (size_t i = 0; i < array.size(); ++i) {
            if (i > 0) { *itr++ = ','; }
            if (indent > -1) {
                this->indent(itr, attr, indent);
            }
            if (!this->serialize(itr, array[i], attr, indent, errorMessage)) {
                return false;
            }
        }
        if (indent > -1) {
            --indent;
            if (!array.empty()) {
                this->indent(itr, attr, indent);
            }
        }
        *itr++ = ']';
        break;
    }
    default: break;
    }
    return true;
}

template<typename Iter> inline void Serializer::serialize_string(Iter& itr, const String& value) {
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
    *itr++ = '"';
    for (size_t i = 0; i < value.size(); ++i) {
        const char ch = kEscape[static_cast<uint8_t>(value[i])];
        if (ch == 0) {
            *itr++ = value[i];
        } else {
            *itr++ = '\\';
            *itr++ =  ch;
            if (ch == 'u') {
                *itr++ = '0';
                *itr++ = '0';
                *itr++ = kHexDigits[(value[i] >> 4) & 0xf];
                *itr++ = kHexDigits[value[i] & 0xf];
            }
        }
    }
    *itr++ = '"';
}

template<typename Iter> inline void Serializer::indent(Iter& itr, const Attributes& attr, const int& indent) {
    if (attr.pretty) {
        this->append(itr, attr.lineBreak);
        for (int i = 0; i < indent; ++i) {
            this->append(itr, attr.tab);
        }
    }
}
template<typename Iter> inline void Serializer::append(Iter& itr, const String& app) {
    for (size_t i = 0; i < app.size(); ++i) {
        *itr++ = app[i];
    }
}

} // namespace pocketjson

#endif // POCKETJSON_H
