/**
 *  ValueDouble.h
 *
 *  Value of numeric type
 *
 *  @copyright 2014 Copernica BV
 */

/**
 *  Include guard
 */
#pragma once

#include "../include/ValueImpl.h"

/**
 *  Set up namespace
 */
namespace Variant {

/**
 *  Numeric value implementation
 */
class ValueDouble : public ValueImpl
{
private:
    /**
     *  Value of this value
     */
    double _value;
public:
    /**
     *  Get the implementation type
     */
    virtual ValueType type() const override
    {
        return ValueDoubleType;
    }

    /**
     *  Clone the implementation
     */
    virtual ValueImpl* clone() const override
    {
        return new ValueDouble(_value);
    }

    /**
     *  Construct new integer value
     *
     *  @param  value
     */
    ValueDouble(double value) : _value(value) {}

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
    virtual operator int32_t () const override
    {
        return _value;
    }

    /**
     *  Convert the value to a number
     */
    virtual operator int64_t () const override
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
        return json_object_new_double(_value);
    }

    /**
     *  Comparison operator
     */
    virtual bool operator==(const ValueImpl &that) const override
    {
        // Start off with checking if we are the same type
        if (that.type() != ValueDoubleType) return false;

        // Cast that to a double
        double d = that;

        // Compare the two doubles
        return _value == d;
    }
};

/**
 *  End namespace
 */
}