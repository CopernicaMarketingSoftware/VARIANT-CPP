/**
 *  ValueVector.h
 *
 *  Value value holding a number of values
 *  indexed by number.
 *
 *  @copyright 2014 Copernica BV
 */

/**
 *  Include guard
 */
#ifndef __COPERNICA_VARIANT_VALUEVECTOR_H
#define __COPERNICA_VARIANT_VALUEVECTOR_H

#include "../include/ValueImpl.h"
#include "../include/Value.h"
#include <vector>

/**
 *  Set up namespace
 */
namespace Variant {

/**
 *  Set up class
 */
class ValueVector : public ValueImpl
{
private:
    /**
     *  The available items
     */
    std::vector<Value> _items;
public:
    /**
     *  Empty constructor
     */
    ValueVector() {}

    /**
     *  Copy constructor
     */
    ValueVector(const ValueVector& that) : _items(that._items) {}

    /**
     *  Move constructor
     */
    ValueVector(ValueVector&& that) : _items(std::move(that._items)) {}

    /**
     *  Constructor with list of items
     */
    ValueVector(const std::vector<Value>& items) : _items(items) {}

    /**
     *  Constructor with moveable list of items
     */
    ValueVector(std::vector<Value>&& items) : _items(std::move(items)) {}

    /**
     *  Constructor with initializer list
     */
    ValueVector(const std::initializer_list<Value>& items) : _items(items) {}

    /**
     *  Get the implementation type
     */
    virtual ValueType type() override
    {
        return ValueVectorType;
    }

    /**
     *  Clone the implementation
     */
    virtual ValueImpl* clone() override
    {
        return new ValueVector(_items);
    }

    /**
     *  Convert the value to a vector
     *
     *  This is only relevant for array value,
     *  it will return an empty vector by default.
     */
    virtual operator std::vector<Value> () const override
    {
        return _items;
    }

    /**
     *  Get the number of items in the array
     */
    virtual size_t size() const override
    {
        return _items.size();
    }

    /**
     *  Retrieve value at given offset
     *
     *  If no value exists at the given offset, a
     *  null value will be returned instead.
     */
    virtual Value get(size_t index) override
    {
        // check for a valid index and return the value
        if (index < size()) return _items[index];

        // invalid offset
        return nullptr;
    }

    /**
     *  Set value at the given offset
     *
     *  This is only applicable for array values,
     *  other implementation will ignore this.
     */
    virtual ValueImpl& set(size_t index, const Value& value) override
    {
        // make sure that the requested offset is available
        while (index > size() - 1) _items.push_back(nullptr);

        // set the value and allow chaining
        _items[index] = value;
        return *this;
    }

    /**
     *  Set value at the given offset
     *
     *  This is only applicable for array values,
     *  other implementation will ignore this.
     */
    virtual ValueImpl& set(size_t index, Value&& value) override
    {
        // make sure that the requested offset is available
        while (index > size() - 1) _items.push_back(nullptr);

        // move the value and allow chaining
        _items[index] = std::move(value);
        return *this;
    }
};

/**
 *  End namespace
 */
}

#endif /* ValueVector.h */
