#include <iostream>

#include "voxel.hh"

Voxel::Voxel(int voxel_idx_) 
    : v_idx(voxel_idx_) {
        v_energy_total = 0.0f;
    }

const int Voxel::get_index() const {
    return v_idx;
}

float Voxel::get_energy_total() const {
    return v_energy_total;
}

