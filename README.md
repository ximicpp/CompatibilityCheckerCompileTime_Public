# Type Signature Generator

A C++ library for generating detailed type signatures at compile-time, providing type information including size, alignment, and structure layout.

## Features

- Compile-time type signature generation
- Support for fundamental types (int32_t, float, double, etc.)
- Support for compound types (structs, vectors, maps)
- Alignment and size information included
- Platform verification through static assertions
- Cross-platform support (Windows, Linux, MacOS, iOS, Android)

## Requirements

- C++17 or later
- Boost 1.81.0 or later
- 64-bit system
- Little-endian architecture

## Dependencies

- Boost.PFR for struct reflection
- Boost.Container for container types
- Boost.Any for type-erased storage

## Usage Example

### Basic Usage

```cpp
#include "type_signature.hpp"
#include <iostream>

namespace test {
    struct Point {
        float x;
        float y;
    };
}

int main() {
    using namespace type_signature;
    print_type_signature<test::Point>("Point");
    return 0;
}
```

### Type Signature Format

The type signature format follows these patterns:
- Basic types: `type[s:size,a:alignment]`
- Structs: `struct[s:size,a:alignment]{@offset:member_type,...}`
- Containers: `container[s:size,a:alignment]<element_type>`

Examples:
```cpp
// Basic types
static_assert(get_type_signature<int32_t>() == "i32[s:4,a:4]");
static_assert(get_type_signature<float>() == "f32[s:4,a:4]");

// Simple struct
struct Point {
    float x;
    float y;
};
// Signature: struct[s:8,a:4]{@0:f32[s:4,a:4],@4:f32[s:4,a:4]}

// Complex struct with containers
struct TestType2 {
    int32_t mInt;
    XString mStr;
    XVector<int32_t> mVector;
};
// Signature: struct[s:56,a:8]{@0:i32[s:4,a:4],@8:string[s:24,a:8],@32:vector[s:24,a:8]<i32[s:4,a:4]>}
```

## Supported Types

### Fundamental Types
- int32_t, uint32_t
- float, double
- Fixed-size arrays
- Pointers

### Container Types
- XString (boost::container::string)
- XVector (boost::container::vector)
- XMap (boost::container::flat_map)

### Custom Types
- User-defined structs
- Nested structures
- Type-erased storage (XAny)

## Platform Verification

The library includes static assertions to verify:
- 64-bit architecture
- Little-endian byte order
- Fundamental type sizes
- Alignment requirements

## Technical Details

### Compile-Time Computation
- All type signatures are generated at compile-time with zero runtime overhead
- Uses template metaprogramming and compile-time string manipulation
- Leverages Boost.PFR for compile-time struct reflection

### Platform Requirements
- Supports Windows (MSVC) and Linux (GCC/Clang)
- Requires proper structure alignment and packing
- Platform-specific type sizes must match expected values

## Important Notes

1. Structure Layout:
   - Ensure structures use correct alignment attributes
   - Be aware that compiler optimizations may affect structure layout

2. Type Constraints:
   - All type sizes must be less than or equal to ANY_SIZE (64 bytes)
   - Pointer size must be 8 bytes
   - Basic type sizes must conform to standard requirements