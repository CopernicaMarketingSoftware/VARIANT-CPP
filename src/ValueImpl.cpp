/**
 *  ValueImpl.h
 *
 *  Implementation file for the different value types
 *
 *  @copyright 2014 Copernica BV
 */

#include "../include/ValueImpl.h"
#include "../include/Value.h"

/**
 *  Set up namespace
 */
namespace Variant {

/**
 *  Convert the value to a boolean
 */
ValueImpl::operator bool () const
{
    return false;
}

/**
 *  Convert the value to a number
 */
ValueImpl::operator int () const
{
    return 0;
}

ValueImpl::operator long () const
{
    return 0;
}

/**
 *  Convert the value to a number
 */
ValueImpl::operator double () const
{
    return 0;
}

/**
 *  Convert the value to a string
 */
ValueImpl::operator std::string () const
{
    return "";
}

/**
 *  Convert the value to a vector
 *
 *  This is only relevant for array values,
 *  it will return an empty vector by default.
 */
ValueImpl::operator std::vector<Value> () const
{
    return {};
}

/**
 *  Convert the value to a map
 *
 *  This is only relevant for map values,
 *  it will return an empty map by default.
 */
ValueImpl::operator std::map<std::string, Value> () const
{
    return {};
}

/**
 *  The number of items in this implementation
 *
 *  This is only relevant for either the array
 *  or map implementations, so it returns zero
 *  by default.
 */
size_t ValueImpl::size() const
{
    return 0;
}

/**
 *  Retrieve value at the given offset
 *
 *  This is only applicable for array values,
 *  so it returns a null value by default.
 */
Value ValueImpl::get(size_t index) const
{
    return nullptr;
}

/**
 *  Set value at the given offset
 *
 *  This is only applicable for array values,
 *  other implementation will ignore this.
 */
ValueImpl& ValueImpl::set(size_t index, const Value& value)
{
    return *this;
}

/**
 *  Set value at the given offset
 *
 *  This is only applicable for array values,
 *  other implementation will ignore this.
 */
ValueImpl& ValueImpl::set(size_t index, Value&& value)
{
    return *this;
}

/**
 *  Retrieve value at the given key
 *
 *  This is only applicable for map values
 *  so it returns a null value by default.
 */
Value ValueImpl::get(const std::string& key) const
{
    return nullptr;
}

/**
 *  Set value at the given key
 *
 *  This is only applicable for map value,
 *  other implementation will ignore this.
 */
ValueImpl& ValueImpl::set(const std::string& key, const Value& value)
{
    return *this;
}

/**
 *  Set value at the given key
 *
 *  This is only applicable for map values,
 *  other implementation will ignore this.
 */
ValueImpl& ValueImpl::set(const std::string& key, Value&& value)
{
    return *this;
}

/**
 *  End namespace
 */
}
