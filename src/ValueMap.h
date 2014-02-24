/**
 *  ValueMap.h
 *
 *  Value value holding a map of
 *  keys and values.
 *
 *  @copyright 2014 Copernica BV
 */

/**
 *  Include guard
 */
#ifndef __COPERNICA_VARIANT_VALUEMAP_H
#define __COPERNICA_VARIANT_VALUEMAP_H

#include "../include/ValueImpl.h"
#include "../include/Value.h"
#include <map>

/**
 *  Set up namespace
 */
namespace Variant {

/**
 *  Set up class
 */
class ValueMap : public ValueImpl
{
private:
    /**
     *  The available items
     */
    std::map<std::string, Value> _items;
public:
    /**
     *  Empty constructor
     */
    ValueMap() {}

    /**
     *  Copy constructor
     */
    ValueMap(const ValueMap& that) : _items(that._items) {}

    /**
     *  Move constructor
     */
    ValueMap(ValueMap&& that) : _items(std::move(that._items)) {}

    /**
     *  Constructor with list of items
     */
    ValueMap(const std::map<std::string, Value>& items) : _items(items) {}

    /**
     *  Constructor with moveable list of items
     */
    ValueMap(std::map<std::string, Value>&& items) : _items(std::move(items)) {}

    /**
     *  Constructor with initializer list
     */
    ValueMap(const std::initializer_list<std::map<std::string, Value>::value_type>& items) : _items(items) {}

    /**
     *  Get the implementation type
     */
    virtual ValueType type() override
    {
        return ValueMapType;
    }

    /**
     *  Clone the implementation
     */
    virtual ValueImpl* clone() override
    {
        return new ValueMap(_items);
    }

    /**
     *  Convert the value to a map
     *
     *  This is only relevant for map values,
     *  it will return an empty map by default.
     */
    virtual operator std::map<std::string, Value> () const override
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
    virtual Value get(const std::string& key) override
    {
        try
        {
            // if the element exists, return it
            return _items.at(key);
        }
        catch (const std::out_of_range& e)
        {
            // element does not exist, return null instead
            return nullptr;
        }
    }

    /**
     *  Set value at the given key
     *
     *  This is only applicable for map values,
     *  other implementation will ignore this.
     */
    virtual ValueImpl& set(const std::string& key, const Value& value) override
    {
        // set property and allow chaining
        _items[key] = value;
        return *this;
    }

    /**
     *  Set value at the given key
     *
     *  This is only applicable for map values,
     *  other implementation will ignore this.
     */
    virtual ValueImpl& set(const std::string& key, Value&& value) override
    {
        // move property and allow chaining
        _items[key] = std::move(value);
        return *this;
    }
};

/**
 *  End namespace
 */
}

#endif /* ValueMap.h */
