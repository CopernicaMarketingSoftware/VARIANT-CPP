/**
 *  ValueNull.h
 *
 *  Value of null type
 *
 *  @copyright 2014 Copernica BV
 */

/**
 *  Include guard
 */
#ifndef __COPERNICA_VARIANT_VALUENULL_H
#define __COPERNICA_VARIANT_VALUENULL_H

#include "../include/ValueImpl.h"
#include <cstdlib>

/**
 *  Set up namespace
 */
namespace Variant {

/**
 *  Null value implementation
 */
class ValueNull : public ValueImpl
{
public:
    /**
     *  Empty constructor
     */
    ValueNull() {}

    /**
     *  Get the implementation type
     */
    virtual ValueType type() const override
    {
        return ValueNullType;
    }

    /**
     *  Clone the implementation
     */
    virtual ValueImpl* clone() const override
    {
        return new ValueNull();
    }

    /**
     *  Turn the value into a json compatible type
     */
    virtual struct json_object *toJson() const override
    {
        return nullptr;
    }

    /**
     *  Comparison operator
     */
    virtual bool operator==(const ValueImpl &that) const override
    {
        // Simply check if the type of that is null
        return that.type() == ValueNullType;
    }
};

/**
 *  End namespace
 */
}

#endif /* ValueNull.h */
