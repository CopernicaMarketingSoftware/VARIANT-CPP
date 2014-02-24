/**
 *  variant.h
 *
 *  A simple library that allows using a single variable for
 *  many types, including integers, strings, vectors and maps.
 *
 *  It is most useful when decoding e.g. json data, where the
 *  exact type is not known beforehand (and thus cannot be
 *  compiled in).
 *
 *  @copyright 2014 Copernica BV
 *  @author Martinj Otto <martijn.otto@copernica.com>
 */

/**
 *  Include relevant header files
 */
#include <variant/Value.h>
#include <variant/ValueMember.h>
