#pragma once

#include "includes.h"
#include "vec.h"

static inline Vec3 sample_HG(const Vec3& w, double g, std::mt19937_64& rng){
    std::uniform_real_distribution<double> U(0.0,1.0);
    double u1=U(rng), u2=U(rng);
    double cost;
    if (std::abs(g) < 1e-12) cost = 2.0*u1 - 1.0;
    else {
        double t = (1.0 - g*g) / (1.0 - g + 2.0*g*u1);
        cost = (1.0 + g*g - t*t) / (2.0*g);
        cost = std::max(-1.0, std::min(1.0, cost));
    }
    double sint = std::sqrt(std::max(0.0, 1.0 - cost*cost));
    double phi = 2.0*M_PI*u2;

    // Build orthonormal basis around w
    Vec3 ez = normalize(w);
    Vec3 a = (std::fabs(ez.z) < 0.999) ? Vec3{0,0,1} : Vec3{1,0,0};
    Vec3 ex = normalize(Vec3{ ez.y*a.z - ez.z*a.y, ez.z*a.x - ez.x*a.z, ez.x*a.y - ez.y*a.x });
    Vec3 ey = Vec3{ ez.y*ex.z - ez.z*ex.y, ez.z*ex.x - ez.x*ex.z, ez.x*ex.y - ez.y*ex.x };

    return normalize( ex*(sint*std::cos(phi)) + ey*(sint*std::sin(phi)) + ez*cost );
}