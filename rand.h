#pragma once

#include <cstdlib>
#include "ray.h"

float random_float(float min, float max) {
    float x = rand() / (RAND_MAX + 1.0);
    return min + x * (max - min);
}

vec3 random_vec_in_sphere() {
    vec3 ret;
    do {
        ret = vec3(random_float(-1, 1), random_float(-1, 1), random_float(-1, 1));
    } while(ret.length() >= 1);
    return unit_vector(ret);
}

vec3 random_in_hemisphere(const vec3& normal) {
    vec3 in_unit_sphere = random_vec_in_sphere();
    if (dot(in_unit_sphere, normal) > 0.0) return in_unit_sphere;
    else return -in_unit_sphere;
}