#include <iostream>
#include <string>
#include <assert.h>
#include <exception>

#include "voxelList.hh"
#include "voxel.hh"
#include "exceptions.hh"

voxelList::voxelList(int num_voxels_)
    : num_voxels(num_voxels_) {}

const int voxelList::get_num_voxels() const{
    return num_voxels;
}

Voxel init_voxel(int idx) {
    Voxel vox(idx);
    return vox;
    //expand later for more cases
    //throws voxel_init_except if problem arises .
}

const int voxelList::initVoxelList() {
    assert(get_num_voxels() > 0 && "ERROR: src/voxel/voxelList.cc -> initVoxelList(), cannot initialize voxel list with length 0\n");
    int count = 0;
    try {
        for(int idx=0;idx<num_voxels;idx++) {
            Voxel vox = init_voxel(idx);
            voxel_list.push_back(vox);
            count++;
        }
    }
    catch (voxel_init_exception& e) {
        std::cerr << e.what() << std::to_string(count) << "at src/voxel/voxelList.cc -> initVoxelList()" << std::endl;
    }
    /*  return num_voxels if all succesfully initialized, otherwise return -1  */
    if(count == num_voxels)
        return count;
    return -1;
}

const int voxelList::set_num_voxels(int num_voxels_) {
    assert(get_num_voxels() > 0 && "ERROR: src/voxel/voxelList.cc -> set_num_voxels(int), cannot set length of voxel list to 0\n");
    assert(get_num_voxels() < num_voxels_ && 
            "ERROR: src/voxel/voxelList.cc -> set_num_voxels(int), cannot set length of voxel list to less than current length");
    num_voxels = num_voxels_;
    int count = 0;
    try {
        for(int idx = voxel_list.size(); idx < num_voxels; idx++) {
            Voxel vox = init_voxel(idx);
            voxel_list.push_back(vox);
            count++;
        }
    }
    catch (voxel_init_exception& e) {
        std::cerr << e.what() << std::to_string(count) << "at src/voxel/voxelList.cc -> set_num_voxels(int)" << std::endl;
    }
    return count;
}
