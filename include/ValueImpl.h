/**
 *  ValueImpl.h
 *
 *  Header file for the different value implementations
 *
 *  @copyright 2014 Copernica BV
 */

/**
 *  Include guard
 */
#ifndef __COPERNICA_VARIANT_VALUEIMPL_H
#define __COPERNICA_VARIANT_VALUEIMPL_H

#include "ValueBase.h"
#include <memory>
#include <vector>
#include <map>

/**
 *  Set up namespace
 */
namespace Variant {

/**
 *  The available value types
 */
typedef enum _ValueTypes {
    ValueNullType,
    ValueIntType,
    ValueStringType,
    ValueVectorType,
    ValueMapType
} ValueType;

/**
 *  ValueImpl interface
 */
class ValueImpl : public ValueBase
{
public:
    /**
     *  Destructor
     */
    virtual ~ValueImpl() {}

    /**
     *  Get the implementation type
     */
    virtual ValueType type() = 0;

    /**
     *  Clone the implementation
     */
    virtual ValueImpl* clone() = 0;

    /**
     *  Convert the value to a number
     */
    virtual operator int ();

    /**
     *  Convert the value to a string
     */
    virtual operator std::string ();

    /**
     *  Convert the value to a vector
     *
     *  This is only relevant for array values,
     *  it will return an empty vector by default.
     */
    virtual operator std::vector<Value> () const;

    /**
     *  Convert the value to a map
     *
     *  This is only relevant for map values,
     *  it will return an empty map by default.
     */
    virtual operator std::map<std::string, Value> () const;

    /**
     *  The number of items in this implementation
     *
     *  This is only relevant for either the array
     *  or map implementations, so it returns zero
     *  by default.
     */
    virtual size_t size() const;

    /**
     *  Retrieve value at the given offset
     *
     *  This is only applicable for array value,
     *  so it returns a null value by default.
     */
    virtual Value get(size_t index);

    /**
     *  Set value at the given offset
     *
     *  This is only applicable for array values,
     *  other implementation will ignore this.
     */
    virtual ValueImpl& set(size_t index, const Value& value);
    virtual ValueImpl& set(size_t index, Value&& value);

    /**
     *  Retrieve value at the given key
     *
     *  This is only applicable for map values
     *  so it returns a null value by default.
     */
    virtual Value get(const std::string& key);

    /**
     *  Set value at the given key
     *
     *  This is only applicable for map values,
     *  other implementation will ignore this.
     */
    virtual ValueImpl& set(const std::string& key, const Value& value);
    virtual ValueImpl& set(const std::string& key, Value&& value);
};

/**
 *  End namespace
 */
}

#endif /* ValueImpl.h */
