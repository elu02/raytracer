#pragma once

#include "hittable.h"

class material {
    public: 
        virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) = 0;
}; 