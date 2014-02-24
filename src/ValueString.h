/**
 *  ValueString.h
 *
 *  Value of string type
 *
 *  @copyright 2014 Copernica BV
 */

/**
 *  Include guard
 */
#ifndef __COPERNICA_VARIANT_VALUESTRING_H
#define __COPERNICA_VARIANT_VALUESTRING_H

#include "../include/ValueImpl.h"
#include <cstdlib>

/**
 *  Set up namespace
 */
namespace Variant {

/**
 *  String value implementation
 */
class ValueString : public ValueImpl
{
private:
    /**
     *  Value of this value
     */
    std::string _value;
public:
    /**
     *  Construct new string value
     *
     *  @param  value
     */
    ValueString(const char* value) : _value(value) {}

    /**
     *  Construct new string value
     *
     *  @param  value
     */
    ValueString(const char* value, size_t length) : _value(value, length) {}

    /**
     *  Construct new string value
     *
     *  @param  value
     */
    ValueString(const std::string& value) : _value(value) {}

    /**
     *  Construct new string value
     *
     *  @param  value
     */
    ValueString(std::string&& value) : _value(std::move(value)) {}

    /**
     *  Get the implementation type
     */
    virtual ValueType type() override
    {
        return ValueStringType;
    }

    /**
     *  Clone the implementation
     */
    virtual ValueImpl* clone() override
    {
        return new ValueString(_value);
    }

    /**
     *  Convert the value to a number
     */
    virtual operator int () override
    {
        return atoi(_value.c_str());
    }

    /**
     *  Convert the value to a string
     */
    virtual operator std::string () override
    {
        return _value;
    }
};

/**
 *  End namespace
 */
}

#endif /* ValueString.h */
