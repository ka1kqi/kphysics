#ifndef KPHYSICS_SRC_VOXEL_VOXELLIST_H
#define KPHYSICS_SRC_VOXEL_VOXELLIST_H

#include <iostream>
#include <string>
#include "voxel.hh"

 
/************************************
container for list of voxels
************************************/
class voxelList {
    std::vector<Voxel> voxel_list;
    int num_voxels;
public: 
    explicit voxelList(int num_voxels);
    const int get_num_voxels() const;
    const int set_num_voxels(int voxel_num);
    const int initVoxelList();
};

#endif