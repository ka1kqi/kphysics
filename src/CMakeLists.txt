cmake_minimum_required(VERSION 3.10)
set(PROJECT_NAME kphysics)
project(${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

set(SOURCES main.cc
            voxel/voxel.hh
            voxel/voxel.cc
            utils/exceptions.hh
            voxel/voxelList.hh
            voxel/voxelList.cc)

add_executable(kphysics ${SOURCES})
target_include_directories(kphysics PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

