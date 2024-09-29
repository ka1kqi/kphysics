//standard library includes
#include <iostream>
#include <string>
#include <assert.h>

//project includes
#include "voxelList.hh"
#include "voxel.hh"

voxelList::voxelList(int num_voxels_, std::string sim_particle_type_)
    : num_voxels(num_voxels_), 
      sim_particle_type(sim_particle_type_) {}

void voxelList::set_voxel_num(int num_voxels_) {
    num_voxels = num_voxels_;
}

const int voxelList::get_num_voxels() const{
    return num_voxels;
}

const int voxelList::initVoxelList() {
    assert(get_num_voxels() > 0 && "ERROR: src/voxel/voxelList.cc -> initVoxelList(), cannot initialize voxel list with length 0\n");
    for(int idx=0;idx<num_voxels;idx++) {
        voxelList::voxel_list.push_back(Voxel(idx));
    }
}