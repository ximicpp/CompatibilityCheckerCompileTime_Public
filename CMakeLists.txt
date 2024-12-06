cmake_minimum_required(VERSION 3.14...3.31)
project(type_check)

# Set policies
cmake_policy(SET CMP0144 NEW)  # for BOOST_ROOT
if(POLICY CMP0167)
    cmake_policy(SET CMP0167 NEW)  # for FindBoost
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Boost configuration
set(BOOST_ROOT ${CMAKE_SOURCE_DIR}/libs/boost_1_81_0)
set(Boost_NO_SYSTEM_PATHS ON)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

if(ANDROID)
    set(ANDROID_STL c++_shared)
    set(Boost_ARCHITECTURE "-a${ANDROID_ARCH_NAME}")
endif()

# Find Boost headers only
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.81.0 COMPONENTS headers)
if(NOT Boost_FOUND)
    # Fallback to include directory only
    if(EXISTS ${BOOST_ROOT}/boost)
        set(Boost_INCLUDE_DIRS ${BOOST_ROOT})
        set(Boost_FOUND TRUE)
    else()
        message(FATAL_ERROR "Boost headers not found in ${BOOST_ROOT}")
    endif()
endif()

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${Boost_INCLUDE_DIRS}
)

# Add source files
set(SOURCES
    src/main.cpp
)

# Create executable
if(IOS OR ANDROID)
    add_executable(type_check MACOSX_BUNDLE ${SOURCES})
else()
    add_executable(type_check ${SOURCES})
endif()

# Set warning flags
if(MSVC)
    target_compile_options(type_check PRIVATE /W4)
else()
    target_compile_options(type_check PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Platform specific settings
if(IOS)
    set(CMAKE_XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer")
    set(CMAKE_XCODE_ATTRIBUTE_DEVELOPMENT_TEAM "")
    
    set_target_properties(type_check PROPERTIES
        MACOSX_BUNDLE TRUE
        XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "${CMAKE_XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY}"
        XCODE_ATTRIBUTE_DEVELOPMENT_TEAM "${CMAKE_XCODE_ATTRIBUTE_DEVELOPMENT_TEAM}"
        XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET "13.0"
        XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "1,2"
    )
elseif(ANDROID)
    # Android specific settings
    set_target_properties(type_check PROPERTIES
        ANDROID_STL c++_shared
        ANDROID_CPP_FEATURES "rtti exceptions"
        ANDROID_TOOLCHAIN clang
    )
endif()

# For header-only Boost libraries, we don't need to link anything
if(Boost_LIBRARIES)
    target_link_libraries(type_check PRIVATE ${Boost_LIBRARIES})
endif()