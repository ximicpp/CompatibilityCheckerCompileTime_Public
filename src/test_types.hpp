#pragma once
#include "type_signature.hpp"

namespace test {
    using namespace type_signature;

    // Verify specific type sizes
    static_assert(sizeof(bool) <= ANY_SIZE, "bool size exceeds ANY_SIZE bytes");
    static_assert(sizeof(int) <= ANY_SIZE, "int size exceeds ANY_SIZE bytes");
    static_assert(sizeof(float) <= ANY_SIZE, "float size exceeds ANY_SIZE bytes");
    static_assert(sizeof(double) <= ANY_SIZE, "double size exceeds ANY_SIZE bytes");
    static_assert(sizeof(XString) <= ANY_SIZE, "string size exceeds ANY_SIZE bytes");
    static_assert(sizeof(XMap<int, int>) <= ANY_SIZE, "map size exceeds ANY_SIZE bytes");
    static_assert(sizeof(XVector<int>) <= ANY_SIZE, "vector size exceeds ANY_SIZE bytes");

    // Test structures
    struct Point {
        float x;
        float y;
    };

    struct Rectangle {
        Point top_left;
        Point bottom_right;
        XString name;
    };

    struct alignas(BASIC_ALIGNMENT) TestType {
        int32_t mInt;

        struct alignas(BASIC_ALIGNMENT) TestTypeInner {
            int32_t mInt;
            XVector<int32_t> mVector;
        } TestTypeInnerObj;

        XMap<XString, TestTypeInner> mComplexMap;
    };

    struct alignas(BASIC_ALIGNMENT) TestType2 {
        int32_t mInt;
        XString mStr;
        XVector<int32_t> mVector;
    };

    // Type signature verification
    static_assert(get_type_signature<int32_t>() == "i32[s:4,a:4]");
    static_assert(get_type_signature<float>() == "f32[s:4,a:4]");
    static_assert(get_type_signature<Point>() ==
                 "struct[s:8,a:4]{@0:f32[s:4,a:4],@4:f32[s:4,a:4]}");
    static_assert(get_type_signature<Rectangle>() ==
                 "struct[s:40,a:8]{@0:struct[s:8,a:4]{@0:f32[s:4,a:4],@4:f32[s:4,a:4]},@8:struct[s:8,a:4]{@0:f32[s:4,a:4],@4:f32[s:4,a:4]},@16:string[s:24,a:8]}");
    static_assert(get_type_signature<TestType>() ==
                 "struct[s:64,a:8]{@0:i32[s:4,a:4],@8:struct[s:32,a:8]{@0:i32[s:4,a:4],@8:vector[s:24,a:8]<i32[s:4,a:4]>},@40:map[s:24,a:8]<string[s:24,a:8],struct[s:32,a:8]{@0:i32[s:4,a:4],@8:vector[s:24,a:8]<i32[s:4,a:4]>}>}");
    static_assert(get_type_signature<TestType2>() ==
                 "struct[s:56,a:8]{@0:i32[s:4,a:4],@8:string[s:24,a:8],@32:vector[s:24,a:8]<i32[s:4,a:4]>}");
    static_assert(get_type_signature<XVector<int32_t>>() == 
                 "vector[s:24,a:8]<i32[s:4,a:4]>");
    static_assert(get_type_signature<XMap<XString, int32_t>>() == 
                 "map[s:24,a:8]<string[s:24,a:8],i32[s:4,a:4]>");
    static_assert(get_type_signature<char[ANY_SIZE]>() == 
                 "bytes[s:64,a:1]");
    static_assert(get_type_signature<void*>() == 
                 "ptr[s:8,a:8]");
    static_assert(get_type_signature<any_equivalent>() ==
                 "struct[s:72,a:8]{@0:ptr[s:8,a:8],@8:ptr[s:8,a:8]}");
    static_assert(get_type_signature<DynamicStruct>() ==
                 "map[s:24,a:8]<string[s:24,a:8],struct[s:72,a:8]{@0:ptr[s:8,a:8],@8:ptr[s:8,a:8]}>");

} // namespace test