/**
 *  ValueMember.h
 *
 *  A value member represents a value located
 *  at a certain index or key in another value
 *
 *  @copyright 2014 Copernica BV
 */

/**
 *  Include guard
 */
#pragma once

#include "ValueImpl.h"

/**
 *  Namespace
 */
namespace Variant {

// forward declaration
class Value;

/**
 *  Value member class
 */
template <typename T>
class ValueMember : private ValueBase
{
private:
    /**
     *  The base we are working with
     */
    ValueBase *_base;

    /**
     *  The index we are modifying
     */
    T _index;

    /**
     *  Retrieve value at the given offset
     *
     *  This is only applicable for array values,
     *  so it returns a null value by default.
     */
    virtual Value get(size_t index) const
    {
        return _base->get(_index)[index];
    }

    /**
     *  Set value at the given offset
     *
     *  This is only applicable for array value,
     *  other implementation will ignore this.
     */
    virtual ValueBase& set(size_t index, const Value& value)
    {
        // retrieve current value and set index
        auto result = _base->get(_index);
        result[index] = value;

        // store the updated value and allow chaining
        _base->set(_index, result);
        return *this;
    }

    /**
     *  Set value at the given offset
     *
     *  This is only applicable for array values,
     *  other implementation will ignore this.
     */
    virtual ValueBase& set(size_t index, Value&& value)
    {
        // retrieve current value and set index
        auto result = _base->get(_index);
        result[index] = std::move(value);

        // store the updated value and allow chaining
        _base->set(_index, result);
        return *this;
    }

    /**
     *  Retrieve value at the given key
     *
     *  This is only applicable for mapvalues
     *  so it returns a null value by default.
     */
    virtual Value get(const std::string& key) const
    {
        return _base->get(_index)[key];
    }

    /**
     *  Set value at the given key
     *
     *  This is only applicable for map values,
     *  other implementation will ignore this.
     */
    virtual ValueBase& set(const std::string& key, const Value& value)
    {
        // retrieve current value and set index
        auto result = _base->get(_index);
        result[key] = value;

        // store the updated value and allow chaining
        _base->set(_index, result);
        return *this;
    }

    /**
     *  Set value at the given key
     *
     *  This is only applicable for map values,
     *  other implementation will ignore this.
     */
    virtual ValueBase& set(const std::string& key, Value&& value)
    {
        // retrieve current value and set index
        auto result = _base->get(_index);
        result[key] = std::move(value);

        // store the updated value and allow chaining
        _base->set(_index, result);
        return *this;
    }
public:
    /**
     *  Constructor
     *
     *  @param  base    base object we modify
     *  @param  index   the index we are working at
     */
    ValueMember(ValueBase* base, T index) : _base(base), _index(index) {}

    /**
     *  Get the value object
     */
    Value value() const
    {
        return _base->get(_index);
    }

    /**
     *  Cast to a value object
     */
    operator Value () const
    {
        return _base->get(_index);
    }

    /**
     *  Cast to a boolean
     */
    operator bool () const
    {
        return _base->get(_index);
    }

    /**
     *  Cast to integer
     */
    operator int32_t () const
    {
        return _base->get(_index);
    }

    /**
     *  Cast to integer
     */
    operator int64_t () const
    {
        return _base->get(_index);
    }

    /**
     *  Cast to a double
     */
    operator double () const
    {
        return _base->get(_index);
    }

    /**
     *  Cast to string
     */
    operator std::string () const
    {
        return _base->get(_index);
    }

    /**
     *  Assignment operator
     *
     *  @param  value
     */
    ValueMember& operator=(const Value& value)
    {
        _base->set(_index, value);
        return *this;
    }

    /**
     *  Assignment operator
     *
     *  @param  value
     */
    ValueMember& operator=(Value&& value)
    {
        _base->set(_index, std::move(value));
        return *this;
    }

    /**
     *  Cast to a vector
     */
    operator std::vector<Value> () const
    {
        return value();
    }

    /**
     *  Assign a vector
     *
     *  @param  value
     */
    ValueMember& operator=(const std::vector<Value>& value)
    {
        _base->set(_index, value);
        return *this;
    }

    /**
     *  Move a vector
     */
    ValueMember& operator=(std::vector<Value>&& value)
    {
        _base->set(_index, std::move(value));
        return *this;
    }

    /**
     *  Cast to a map
     */
    operator std::map<std::string, Value> () const
    {
        return value();
    }

    /**
     *  Assign a map
     *
     *  @param  value
     */
    ValueMember& operator=(const std::map<std::string, Value>& value)
    {
        _base->set(_index, value);
        return *this;
    }

    /**
     *  Move a map
     *
     *  @param  value
     */
    ValueMember& operator=(std::map<std::string, Value>&& value)
    {
        _base->set(_index, std::move(value));
        return *this;
    }

    /**
     *  Array access operator
     *  @param  index
     */
    ValueMember<int> operator [] (int index)
    {
        return ValueMember<int>(this, index);
    }

    /**
     *  Array access operator
     *  @param  index
     */
    ValueMember<std::string> operator [] (const char* key)
    {
        return ValueMember<std::string>(this, std::string{key});
    }

    /**
     *  Array access operator
     *  @param  index
     */
    ValueMember<std::string> operator [] (const std::string& key)
    {
        return ValueMember<std::string>(this, key);
    }

    /**
     *  Equals and not equals to operators
     */
    bool operator==(const ValueMember &that) const { return value() == that.value(); }
    bool operator!=(const ValueMember &that) const { return value() != that.value(); }
};

/**
 *  End namespace
 */
}