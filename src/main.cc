#include <iostream>
#include "voxel/voxelList.hh"

int main(void) {
    voxelList vox_list(10,ALPHA);
    vox_list.initVoxelList();
    std::cout<< "Voxel list initalized\n";
    return 0;
}