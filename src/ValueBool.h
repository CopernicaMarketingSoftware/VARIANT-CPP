/**
 *  ValueBool.h
 *
 *  Value of boolean type
 *
 *  @copyright 2014 Copernica BV
 */

/**
 *  Include guard
 */
#ifndef __COPERNICA_VARIANT_VALUEBOOL_H
#define __COPERNICA_VARIANT_VALUEBOOL_H

#include "../include/ValueImpl.h"

/**
 *  Set up namespace
 */
namespace Variant {

/**
 *  Numeric value implementation
 */
class ValueBool : public ValueImpl
{
private:
    /**
     *  Value of this value
     */
    bool _value;
public:
    /**
     *  Get the implementation type
     */
    virtual ValueType type() override
    {
        return ValueBoolType;
    }

    /**
     *  Clone the implementation
     */
    virtual ValueImpl* clone() override
    {
        return new ValueBool(_value);
    }

    /**
     *  Construct new integer value
     *
     *  @param  value
     */
    ValueBool(bool value) : _value(value) {}

    /**
     *  Convert the value to a boolean
     */
    virtual operator bool () override
    {
        return _value;
    }

    /**
     *  Convert the value to a number
     */
    virtual operator int () override
    {
        return _value;
    }

    /**
     *  Convert the value to a number
     */
    virtual operator double() override
    {
        return _value;
    }

    /**
     *  Convert the value to a string
     */
    virtual operator std::string () override
    {
        return std::to_string(_value);
    }
};

/**
 *  End namespace
 */
}

#endif /* ValueBool.h */
