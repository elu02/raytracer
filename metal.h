#pragma once

#include <iostream>
#include <memory>

#include "material.h"
#include "rand.h"

class metal : public material { 
    public: 
        color albedo;
        float fuzziness;
        metal(color al, float fuzz) : albedo(al), fuzziness(fuzz) {};

        bool scatter(const ray& r, const hit_record& rec, color& attenuation, ray& scattered) override {
            scattered = ray(rec.poi, (r.direction() - 2 * dot(r.direction(), rec.N) * rec.N)
                            + fuzziness * random_vec_in_sphere());
            attenuation = albedo;
            return (dot(scattered.direction(), rec.N) > 0);
        }
};