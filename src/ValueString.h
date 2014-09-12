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
#pragma once

#include "../include/ValueImpl.h"

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
    virtual ValueType type() const override
    {
        return ValueStringType;
    }

    /**
     *  Clone the implementation
     */
    virtual ValueImpl* clone() const override
    {
        return new ValueString(_value);
    }

    /**
     *  Convert the value to a boolean
     */
    virtual operator bool () const override
    {
        // cast to a number and see whether this is false
        try
        {
            return std::stod(_value);
        }
        catch (...)
        {
            return 0;
        }
    }

    /**
     *  Convert the value to a number
     */
    virtual operator int32_t () const override
    {
        try
        {
            return std::stoi(_value);
        }
        catch (...)
        {
            return 0;
        }
    }

    /**
     *  Convert the value to a number
     */
    virtual operator int64_t () const override
    {
        try
        {
            return std::stoll(_value);
        }
        catch (...)
        {
            return 0;
        }
    }

    /**
     *  Convert the value to a number
     */
    virtual operator double () const override
    {
        try
        {
            return std::stod(_value);
        }
        catch (...)
        {
            return 0.0;
        }
    }

    /**
     *  Convert the value to a string
     */
    virtual operator std::string () const override
    {
        return _value;
    }

    /**
     *  Turn the value into a json compatible type
     */
    virtual struct json_object *toJson() const override
    {
        return json_object_new_string_len(_value.data(), _value.size());
    }

    /**
     *  Comparison operator
     */
    virtual bool operator==(const ValueImpl &that) const override
    {
        // Start off with checking if we are the same type
        if (that.type() != ValueStringType) return false;

        // Cast that to a std::string
        std::string s = that;

        // Compare the two strings
        return _value == s;
    }
};

/**
 *  End namespace
 */
}