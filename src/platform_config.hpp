#pragma once

// Platform detection
#if defined(_MSC_VER)
    #define TYPESIG_PLATFORM_WINDOWS 1
    #define IS_LITTLE_ENDIAN 1
#else
    #define TYPESIG_PLATFORM_WINDOWS 0
    #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
        #define IS_LITTLE_ENDIAN 1
    #else
        #define IS_LITTLE_ENDIAN 0
    #endif
#endif

namespace type_signature {
    inline constexpr int BASIC_ALIGNMENT = 8;
    inline constexpr int ANY_SIZE = 64;
}