#ifndef KPHYSICS_SRC_VOXEL_VOXELLIST_H
#define KPHYSICS_SRC_VOXEL_VOXELLIST_H

#include <iostream>
#include <string>
#include "voxel.hh"

const std::string ALPHA = "alpha";
 
/************************************
container for list of voxels
************************************/
class voxelList {
    std::vector<Voxel> voxel_list;
    int num_voxels;
    std::string sim_particle_type;
public: 
    explicit voxelList(int num_voxels, std::string sim_particle_type);
    const int get_num_voxels() const;
    void set_voxel_num(int voxel_num);
    const int initVoxelList();
};


#endif