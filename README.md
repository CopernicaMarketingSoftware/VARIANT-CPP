VARIANT-CPP
===========

The VARIANT-CPP library is a simply library that can be used in cases where the exact type of function parameters or return values
is not known in advance. This is mostly useful in cases where serialized data is retrieved.

The variant can represent either an integer, a string, a vector or a map:

```c
// construct value to be an integer
Variant::Value value = 10;

// it can switch type during its lifetime
value = "we are now a string";

// or it can be a vector of values of different types
value = {
    Variant::Value("Value at index 0"),
    Variant::Value(1)
};
```
