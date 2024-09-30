#include <iostream>
#include "voxel/voxelList.hh"

int main(void) {
    voxelList vox_list(10);
    vox_list.initVoxelList();
    vox_list.set_num_voxels(15);
    std::cout<< "Voxel list initalized\n";
    return 0;
}