VARIANT-CPP
===========

The VARIANT-CPP library is a simply library that offers a Variant::Value class that 
can be used to store variables of almost any type. This could be useful for C++
programs that communicate with other technologies that are not strongly typed.

Currently, the value objects can represent either an integer, a string, a vector 
of variants or a string-indexed map of variants:

````c++
#include <variant.h>

int main()
{
    // construct value to be an integer
    Variant::Value value = 10;
    
    // it can switch type during its lifetime
    value = "we are now a string";
    
    // it can also be turned into a regular integer based array, where each
    // entry is also a variant
    value[0] = "abc";
    value[1] = 128;
    
    // or you can use it as a string indexed map to create an assoc array
    // (once again, the values are variants too, so can be of almost any type)
    value["key1"] = 123;
    value["key2"] = "abc";
    
    // because the values are variants, you can also nest [] operators:
    value["key3"][0] = 123;
    value["key3"][1] = "abc";
    value["key3"][2][0] = 0;
    
    // casting operators have been implemented, so once a value is stored
    // in a variant, you can assign it to a regular C++ variable, the value
    // object will do its best to convert it to an appropriate value
    int x = value;
    int y = value[2];
    std::string z = value["key"][0];
    
    // a value can also be constructed or updated with an initializer list
    // containing variants itself (that of course do not have to be of the
    // same type)
    value = {
        Variant::Value("Value at index 0"),
        Variant::Value(1)
    };
    
    // a value can be casted to a vector or a map
    std::vector<Variant::Value> vector = value;
    std::map<std::string,Variant::Value> map = value;
    
    // done 
    return 0;
}
````

INSTALLATION
============

After you've downloaded the source code, you should compile and install the
library by running the following two commands. This works on all regular
Linux platforms.

````sh
make
sudo make install
````

If you encounter problems when compiling the software, you can make changes
to src/Makefile. On top of this file the most important compile options
are set and they can be easily changed.

To use the library, simply add '#include <variant.h>' on top of your C++
source file. Be aware that this is a C++11 library, so C++11 support should
be enabled.


