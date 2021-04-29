#pragma once

#include "material.h"
#include "texture.h"
#include "rand.h"

#include <memory>

class matte : public material {
    public: 
        std::shared_ptr<texture> albedo;

        matte(std::shared_ptr<texture> al) : albedo(al) {};
        bool scatter(const ray& r, const hit_record& rec, color& attenuation, ray& scattered) override {
            scattered = ray(rec.poi, random_in_hemisphere(rec.N));
            attenuation = albedo->value(rec.u, rec.v);
            return true;
        } 
};