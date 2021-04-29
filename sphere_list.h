#pragma once

#include "vec3.h"
#include "ray.h"
#include "hittable.h"
#include "sphere.h"

#include <memory>

class sphere_list : public hittable {
    public:
        std::shared_ptr<sphere> *lst;
        int len;

        sphere_list(std::shared_ptr<sphere> *l, int n) : lst(l), len(n) {};
        bool hit_test(const ray& r, float tmin, float tmax, hit_record& rec) override {
            bool hit = false;
            rec.t = -1;
            for (int i = 0; i < len; i++) {
                hit_record temp;
                if (lst[i]->hit_test(r, tmin, tmax, temp)) {
                    hit = true;
                    if (rec.t == -1 || rec.t > temp.t) {
                        rec = temp; 
                    }
                }
            }
            return hit;
        };
};