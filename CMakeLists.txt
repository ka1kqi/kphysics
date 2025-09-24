cmake_minimum_required(VERSION 3.15)
project(kphysics VERSION 0.1.0 LANGUAGES CXX)

# Require modern C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enforce out-of-source builds
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source builds are not allowed. Please create a build/ directory and run cmake .. inside it.")
endif()

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    message(STATUS "OpenMP found: enabling parallel build")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
else()
    message(STATUS "OpenMP not found: building single-threaded")
endif()

# Add the src subdirectory (this defines the kphysics library)
add_subdirectory(src)

# Example program (optional, remove if not needed)
add_executable(r70 src/main.cpp)

# Link the example to our library
target_link_libraries(r70 PRIVATE kphysics)

# Add include/ directory so main.cpp can #include "vec.h"
target_include_directories(r70 PRIVATE ${CMAKE_SOURCE_DIR}/include)