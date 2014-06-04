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
    virtual ValueType type() const override
    {
        return ValueVectorType;
    }

    /**
     *  Clone the implementation
     */
    virtual ValueImpl* clone() const override
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
    virtual Value get(size_t index) const override
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

    /**
     *  Turn the value into a json compatible type
     */
    virtual struct json_object *toJson() const override
    {
        // Create a json array
        struct json_object *output = json_object_new_array();

        // Loop through our items and append them to the json array
        for (auto &item : _items) json_object_array_add(output, item.toJson());

        // Return the json array
        return output;
    }

    /**
     *  Comparison operator
     */
    virtual bool operator==(const ValueImpl &that) const override
    {
        // Start off with checking if we are the same type
        if (that.type() != ValueVectorType) return false;

        // Check if we're the same size
        if (that.size() != size()) return false;

        // Cast that to a std::vector
        std::vector<Value> v = that;

        // Store the length of the vector
        std::vector<Value>::size_type len = v.size();

        // Loop through the vector, as soon as we see something that is different we return false
        for (std::vector<Value>::size_type i = 0; i < len; ++i)
        {
            if (v[i] != _items[i]) return false;
        }

        // If we made it here we know that we are the same
        return true;
    }
};

/**
 *  End namespace
 */
}

#endif /* ValueVector.h */
