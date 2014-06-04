/**
 *  ValueInt.h
 *
 *  Value of numeric type
 *
 *  @copyright 2014 Copernica BV
 */

/**
 *  Include guard
 */
#ifndef __COPERNICA_VARIANT_VALUEINT_H
#define __COPERNICA_VARIANT_VALUEINT_H

#include "../include/ValueImpl.h"

/**
 *  Set up namespace
 */
namespace Variant {

/**
 *  Numeric value implementation
 */
class ValueInt : public ValueImpl
{
private:
    /**
     *  Value of this value
     */
    int _value;
public:
    /**
     *  Get the implementation type
     */
    virtual ValueType type() const override
    {
        return ValueIntType;
    }

    /**
     *  Clone the implementation
     */
    virtual ValueImpl* clone() const override
    {
        return new ValueInt(_value);
    }

    /**
     *  Construct new integer value
     *
     *  @param  value
     */
    ValueInt(int value) : _value(value) {}

    /**
     *  Convert the value to a boolean
     */
    virtual operator bool () const override
    {
        return _value;
    }

    /**
     *  Convert the value to a number
     */
    virtual operator int () const override
    {
        return _value;
    }

    /**
     *  Convert the value to a number
     */
    virtual operator double() const override
    {
        return _value;
    }

    /**
     *  Convert the value to a string
     */
    virtual operator std::string () const override
    {
        return std::to_string(_value);
    }

    /**
     *  Turn the value into a json compatible type
     */
    virtual struct json_object *toJson() const override
    {
        return json_object_new_int(_value);
    }

    /**
     *  Comparison operator
     */
    virtual bool operator==(const ValueImpl &that) const override
    {
        // Start off with checking if we are the same type
        if (that.type() != ValueIntType) return false;

        // Cast that to an int
        int i = that;

        // Compare the two integers
        return _value == i;
    }
};

/**
 *  End namespace
 */
}

#endif /* ValueInt.h */
