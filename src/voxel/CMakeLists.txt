target_include_directories(kphysics PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(kphysics PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/voxel.hh)
target_sources(kphysics PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/voxel.cc)
target_sources(kphysics PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/voxelList.hh)
target_sources(kphysics PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/voxelList.cc)