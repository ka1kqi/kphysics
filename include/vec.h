#pragma once
#include "includes.h"

struct Vec3 {
    double x,y,z;
    Vec3 operator+(const Vec3& o) const {return {x+o.x, y+o.y, z+o.z};}
    Vec3 operator-(const Vec3& o) const {return {x-o.x, y-o.y, z-o.z};}
    Vec3 operator*(double s) const { return {x*s,y*s,z*s}; }
};

static inline double dot(const Vec3& a, const Vec3& b) {return a.x*b.x+a.y*b.y+a.z*b.z;}
static inline double norm(const Vec3& a){ return std::sqrt(dot(a,a));}
static inline Vec3 normalize(const Vec3& v){ double n=norm(v); return {v.x/n, v.y/n, v.z/n}; }

