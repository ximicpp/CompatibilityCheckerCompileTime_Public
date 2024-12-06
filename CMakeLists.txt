cmake_minimum_required(VERSION 3.15)
project(type_check VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add Boost
set(BOOST_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/libs/boost_1_81_0)
set(Boost_NO_SYSTEM_PATHS ON)
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.81.0 REQUIRED)

# Add source files
add_executable(type_check
    src/main.cpp
)

# Include directories
target_include_directories(type_check PRIVATE
    ${Boost_INCLUDE_DIRS}
    '${CMAKE_CURRENT_SOURCE_DIR}/src'
)

# Link libraries
target_link_libraries(type_check PRIVATE
    Boost::boost
)

# Platform specific settings
if(ANDROID)
    target_compile_definitions(type_check PRIVATE ANDROID)
elseif(IOS)
    target_compile_definitions(type_check PRIVATE IOS)
    set_target_properties(type_check PROPERTIES
        XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer"
        XCODE_ATTRIBUTE_DEVELOPMENT_TEAM ${DEVELOPMENT_TEAM_ID}
    )
endif()

# Set output directories
set_target_properties(type_check PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)