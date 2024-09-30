#ifndef KPHYSICS_SRC_VOXEL_VOXEL_H
#define KPHYSICS_SRC_VOXEL_VOXEL_H

#include <iostream>


struct Voxel {
    int v_idx;
    float v_energy_total;
    
    explicit Voxel(int voxel_idx_);
    const int get_index() const;
    float get_energy_total() const;
};

#endif