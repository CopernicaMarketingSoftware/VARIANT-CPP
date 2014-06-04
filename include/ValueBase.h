/**
 *  ValueBase.h
 *
 *  @copyright 2014 Copernica BV
 */

// include guard
#ifndef __COPERNICA_VARIANT_VALUEBASE_H
#define __COPERNICA_VARIANT_VALUEBASE_H

#include <string>

/**
 *  Set up namespace
 */
namespace Variant {

// forward declaration
class Value;

/**
 *  Class definition
 */
class ValueBase
{
public:
    /**
     *  Retrieve value at the given offset
     *
     *  This is only applicable for array values,
     *  so it returns a null value by default.
     */
    virtual Value get(size_t index) const = 0;

    /**
     *  Set value at the given offset
     *
     *  This is only applicable for array values,
     *  other implementation will ignore this.
     */
    virtual ValueBase& set(size_t index, const Value& value) = 0;
    virtual ValueBase& set(size_t index, Value&& value) = 0;

    /**
     *  Retrieve value at the given key
     *
     *  This is only applicable for map values
     *  so it returns a null value by default.
     */
    virtual Value get(const std::string& key) const = 0;

    /**
     *  Set value at the given key
     *
     *  This is only applicable for map values,
     *  other implementation will ignore this.
     */
    virtual ValueBase& set(const std::string& key, const Value& value) = 0;
    virtual ValueBase& set(const std::string& key, Value&& value) = 0;
};

/**
 *  End namespace
 */
}

#endif /* ValueBase.h */
