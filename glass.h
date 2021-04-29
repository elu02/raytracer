#pragma once

#include "material.h"
#include "rand.h"

bool refract(const vec3& v, const vec3& n, float ni_div_nt, vec3& refracted) {
    vec3 unit = unit_vector(v);
    float dt = dot(unit, n);
    float disc = 1.0 - ni_div_nt * ni_div_nt * (1 - dt * dt);
    if (disc > 0) {
        refracted = ni_div_nt * (unit - n * dt) - n * sqrt(disc);
        return true;
    }
    return false;
}

float schlick(float cosine, float ref_idx) {
    float r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * std::pow(1 - cosine, 5);
}

class glass : public material { 
    public:
        float index_of_refraction;
        glass(float ind) : index_of_refraction(ind) {};

        bool scatter(const ray& r, const hit_record &rec, color& attenuation, ray& scatter_ray) override {
            attenuation = vec3(1.0, 1.0, 1.0);
            float ni_div_nt, cosine, prob;
            vec3 norm, refracted; 
            if (dot(r.direction(), rec.N) > 0) {       
                norm = -rec.N;
                ni_div_nt = index_of_refraction;
                cosine = index_of_refraction * dot(r.direction(), rec.N) / r.direction().length();
            } else {                                 
                norm = rec.N;
                ni_div_nt = 1.0 / index_of_refraction;  
                cosine = -dot(r.direction(), rec.N) / r.direction().length();
            }
            if (refract(r.direction(), norm, ni_div_nt, refracted)) {
                prob = schlick(cosine, index_of_refraction);
            } else {
                prob = 1.0;
            }
            
            if (random_float(0, 1) < prob) {   
                scatter_ray = ray(rec.poi, (rec.poi - 2 * dot(rec.N, r.direction()) * rec.N));
            } else {
                scatter_ray = ray(rec.poi, refracted);
            }
            return true;
        }
};