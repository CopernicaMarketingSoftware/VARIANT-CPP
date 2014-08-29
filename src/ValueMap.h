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
#pragma once

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
    virtual ValueType type() const override
    {
        return ValueMapType;
    }

    /**
     *  Clone the implementation
     */
    virtual ValueImpl* clone() const override
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
    virtual Value get(const std::string& key) const override
    {
        try
        {
            // if the element exists, return it
            return _items.at(key);
        }
        catch (...)
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

    /**
     *  Turn the value into a json compatible type
     */
    virtual struct json_object *toJson() const override
    {
        // Create a json object
        struct json_object *output = json_object_new_object();

        // Loop through our items and append them to the json object
        for (auto &item : _items) json_object_object_add(output, item.first.data(), item.second.toJson());

        // Return the json array
        return output;
    }

    /**
     *  Comparison operator
     */
    virtual bool operator==(const ValueImpl &that) const override
    {
        // Start off with checking if we are the same type
        if (that.type() != ValueMapType) return false;

        // Check if we're the same size
        if (that.size() != size()) return false;

        // Cast that to a std::map
        std::map<std::string, Value> m = that;

        // Loop through the map and look everything up in the other map
        for (const auto &member : m)
        {
            // Look for an item with the current key in the other map
            const auto &iter = _items.find(member.first);

            // If we didn't find it then we are obviously not equal
            if (iter == _items.end()) return false;

            // If our items aren't equal, neither are we
            if (iter->second != member.second) return false;
        }

        // If we made it here we know that we are the same
        return true;
    }
};

/**
 *  End namespace
 */
}