file(GLOB SOURCES "*.cpp")
add_library(kphysics STATIC ${SOURCES})
target_include_directories(kphysics PUBLIC ${CMAKE_SOURCE_DIR}/include)