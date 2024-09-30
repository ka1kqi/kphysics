cmake_minimum_required(VERSION 3.10)
set(PROJECT_NAME kphysics)
project(${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

add_executable(kphysics src/main.cc)
add_subdirectory(src/utils)
add_subdirectory(src/voxel)

