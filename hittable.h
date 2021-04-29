#pragma once

#include "ray.h"

#include <memory>

class material;

struct hit_record {
    float t;
    vec3 N;
    vec3 poi; 
    std::shared_ptr<material> mat;
    float u, v; // surface coordinates
};

class hittable {
    public:
        virtual bool hit_test(const ray& r, float tmin, float tmax, hit_record& rec) = 0;
};