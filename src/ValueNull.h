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
    virtual ValueType type() override
    {
        return ValueNullType;
    }

    /**
     *  Clone the implementation
     */
    virtual ValueImpl* clone() override
    {
        return new ValueNull();
    }
};

/**
 *  End namespace
 */
}

#endif /* ValueNull.h */
