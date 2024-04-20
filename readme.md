# Overview

This implements bitwise operation for enums (scoped and unscoped).  
For any enum, like

```cpp
enum class EButtons
{
	Left = 1,
	Right = 2,
	Middle = 4,
};
```

you can enable bitwise operations by declaring 

```cpp
enable_bitset_enum(EButtons);
```

A  definition is not required: the function is never called, the declaration
acs as a tag that enables bitwise operations.

# Acknowledgement

I found the idea ... elsewhere. It wasn't the full set of operations,  just a demonstration of the general concept.

# Operations

The operations defined are `|  |=  &  &= ^  ^=  -  -=`

`a-b` and `a-=b` take the place of `a &~ b` and `a &= ~b`, respectively, i.e.,
clearing the bits set in `b`. Negation is not implemented, because that would 
set bits that are not defined in the enum. 

# Type Safety

It's recommended to use scoped enums.

Note that these operations are defined for an unscoped enum, but they yield the
underlying type (usually `int`) instead of the enum. Unscoped enums don't
provide diagnostics when you mix values of different enums:

```cpp
enum EFoo { a = 1, b = 2, c = 4 };
enum EBar { d = 1, e = 2, f = 4 };

// ....

void Test()
{
    auto mix = a | d;       // allowed, no diagnostic
}
```

# c++ 17 vs. c++ 20

There are two implementations: one for C++ 20 using concepts to detect the  "tag" function declaration, the other using `std::enable_if`, compatible wiht C++17.
Except for the tag function detection, they are only marginally different.


