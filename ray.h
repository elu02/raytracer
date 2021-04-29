#pragma once

#include "vec3.h"

class ray { 
    public:
        vec3 orig, dir;
        ray() {};
        ray(const vec3& A, const vec3& b) {
            orig = A;
            dir = b;
        }
        vec3 origin() const { return orig; }
        vec3 direction() const { return dir; }
        vec3 at(float t) const {
            return orig + t * dir;
        }
};