/**
 *  Value.cpp
 *
 *  Value class that can be used as a sort of scripting language
 *  untyped variable.
 *
 *  @copyright 2014
 */

#include "../include/Value.h"
#include "../include/ValueMember.h"
#include "ValueBool.h"
#include "ValueInt.h"
#include "ValueDouble.h"
#include "ValueString.h"
#include "ValueNull.h"
#include "ValueVector.h"
#include "ValueMap.h"

/**
 *  Namespace
 */
namespace Variant {

/**
 *  Copy constructor
 */
Value::Value(const Value& that) : _impl(that._impl->clone()) {}

/**
 *  Move constructor
 */
Value::Value(Value&& that) : _impl(std::move(that._impl)) {}

/**
 *  Null constructor
 */
Value::Value() : _impl(new ValueNull()) {}
Value::Value(std::nullptr_t value) : _impl(new ValueNull()) {}

/**
 *  Boolean constructor
 */
Value::Value(bool value) : _impl(new ValueBool(value)) {}

/**
 *  Numeric constructor
 *  @param  value
 */
Value::Value(int value) : _impl(new ValueInt(value)) {}
Value::Value(double value) : _impl(new ValueDouble(value)) {}

/**
 *  String constructor
 *  @param  value
 */
Value::Value(const char* value) : _impl(new ValueString(value)) {}
Value::Value(const char* value, size_t length) : _impl(new ValueString(value, length)) {}
Value::Value(const std::string& value) : _impl(new ValueString(value)) {}
Value::Value(std::string&& value) : _impl(new ValueString(std::move(value))) {}

/**
 *  Vector constructor
 *  @param  value
 */
Value::Value(const std::vector<Value>& value) : _impl(new ValueVector(value)) {}
Value::Value(std::vector<Value>&& value) : _impl(new ValueVector(std::move(value))) {}
Value::Value(const std::initializer_list<Value>& value) : _impl(new ValueVector(value)) {}

/**
 *  Map constructor
 *  @param  value
 */
Value::Value(const std::map<std::string, Value>& value) : _impl(new ValueMap(value)) {}
Value::Value(std::map<std::string, Value>&& value) : _impl(new ValueMap(std::move(value))) {}
Value::Value(const std::initializer_list<std::map<std::string, Value>::value_type>& value) : _impl(new ValueMap(value)) {}

/**
 *  Get the type of value we are
 */
ValueType Value::type() const
{
    return _impl->type();
}

/**
 *  Assign another value
 *  @param  value
 */
Value& Value::operator=(const Value& value)
{
    // assign implementation and allow chaining
    _impl = ValueImplPtr(value._impl->clone());
    return *this;
}

/**
 *  Assign another value
 *  @param  value
 */
Value& Value::operator=(Value&& value)
{
    // move the implementation
    _impl = std::move(value._impl);
    return *this;
}

/**
 *  Cast to a boolean
 */
Value::operator bool () const
{
    return *_impl;
}

/**
 *  Assign a boolean
 */
Value& Value::operator=(bool value)
{
    _impl = ValueImplPtr(new ValueBool(value));
    return *this;
}

/**
 *  Cast to a number
 */
Value::operator int () const
{
    return *_impl;
}

/**
 *  Cast to a number
 */
Value::operator double () const
{
    return *_impl;
}

/**
 *  Assign a number
 */
Value& Value::operator=(int value)
{
    _impl = ValueImplPtr(new ValueInt(value));
    return *this;
}

/**
 *  Assign a number
 */
Value& Value::operator=(double value)
{
    _impl = ValueImplPtr(new ValueDouble(value));
    return *this;
}

/**
 *  Cast to a string
 */
Value::operator std::string () const
{
    return *_impl;
}

/**
 *  Assign a string
 */
Value& Value::operator=(const char* value)
{
    _impl = ValueImplPtr(new ValueString(value));
    return *this;
}

/**
 *  Assign a string
 */
Value& Value::operator=(const std::string& value)
{
    _impl = ValueImplPtr(new ValueString(value));
    return *this;
}

/**
 *  Move a string
 */
Value& Value::operator=(std::string&& value)
{
    _impl = ValueImplPtr(new ValueString(std::move(value)));
    return *this;
}

/**
 *  Get the number of elements in the variant
 *
 *  This is only applicable for vector and map
 *  types. For any other type, 0 is returned
 */
size_t Value::size() const
{
    return _impl->size();
}

/**
 *  Turn the value into a json compatible type
 */
struct json_object *Value::toJson() const
{
    return _impl->toJson();
}

/**
 *  Turn the value into a json string
 */
std::string Value::toJsonString() const
{
    // Turn our value implementation into a json_object
    struct json_object *json = toJson();

    // Turn this json_object into a string
    std::string output(json_object_to_json_string(json));

    // Decrement the reference count
    json_object_put(json);

    // Return this string
    return output;
}

/**
 *  Cast to an array
 */
Value::operator std::vector<Value> () const
{
    return *_impl;
}

/**
 *  Assign a vector
 */
Value& Value::operator=(const std::initializer_list<Value>& value)
{
    _impl = ValueImplPtr(new ValueVector(value));
    return *this;
}

/**
 *  Assign a vector
 */
Value& Value::operator=(const std::vector<Value>& value)
{
    _impl = ValueImplPtr(new ValueVector(value));
    return *this;
}

/**
 *  Assign a vector
 */
Value& Value::operator=(std::vector<Value>&& value)
{
    _impl = ValueImplPtr(new ValueVector(std::move(value)));
    return *this;
}

/**
 *  Array access operator
 *  @param  index
 */
Value Value::operator [] (int index) const
{
    return _impl->get(index);
}

/**
 *  Overwritable array access operator
 *  @param  index
 */
ValueMember<int> Value::operator [] (int index)
{
    // we must be of the vector type
    if (_impl->type() != ValueVectorType) _impl = ValueImplPtr(new ValueVector());

    // retrieve the offset
    return ValueMember<int>(_impl.get(), index);
}

/**
 *  Cast to a map
 */
Value::operator std::map<std::string, Value> () const
{
    return *_impl;
}

/**
 *  Assign a map
 */
Value& Value::operator=(const std::initializer_list<std::map<std::string, Value>::value_type>& value)
{
    _impl = ValueImplPtr(new ValueMap(value));
    return *this;
}

/**
 *  Assign a map
 */
Value& Value::operator=(const std::map<std::string, Value>& value)
{
    _impl = ValueImplPtr(new ValueMap(value));
    return *this;
}

/**
 *  Assign a map
 */
Value& Value::operator=(std::map<std::string, Value>&& value)
{
    _impl = ValueImplPtr(new ValueMap(std::move(value)));
    return *this;
}

/**
 *  Array access operator
 *  @param  key
 */
const Value Value::operator [] (const char* key) const
{
    return _impl->get(std::string{key});
}

/**
 *  Array access operator
 *  @param  key
 */
const Value Value::operator [] (const std::string& key) const
{
    return _impl->get(key);
}

/**
 *  Overwritable array access operator
 *  @param  key
 */
ValueMember<std::string> Value::operator [] (const char* key)
{
    // we must be of the map type
    if (_impl->type() != ValueMapType) _impl = ValueImplPtr(new ValueMap());

    // retrieve the offset
    return ValueMember<std::string>(_impl.get(), std::string{key});
}

/**
 *  Overwritable array access operator
 *  @param  key
 */
ValueMember<std::string> Value::operator [] (const std::string& key)
{
    // we must be of the map type
    if (_impl->type() != ValueMapType) _impl = ValueImplPtr(new ValueMap());

    // retrieve the offset
    return ValueMember<std::string>(_impl.get(), key);
}

/**
 *  End namespace
 */
}
