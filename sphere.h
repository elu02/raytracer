#pragma once

#include "vec3.h"
#include "hittable.h"
#include "material.h"

#include <memory>
#include <cmath>

const float pi = 3.14159265358979323846;

class sphere : public hittable {
    public:
        vec3 center;
        float radius;
        std::shared_ptr<material> mat;
        sphere(vec3 c, float r, std::shared_ptr<material> m) : center(c), radius(r), mat(m) {};

        bool hit_test(const ray& r, float tmin, float tmax, hit_record& rec) override {
            vec3 b = r.direction();
            vec3 a = r.origin();
            float A = dot(b, b); 
            float B = 2.0 * dot(b, a - center);
            float C = dot(a - center, a - center) - radius * radius;
            float d = B * B - 4.0 * A * C;
            if (d < 0) return false;
            float root1 = (-B - std::sqrt(d)) / (2.0 * A);;
            float root2 = (-B + std::sqrt(d)) / (2.0 * A);
            if (root1 > tmin && root1 < tmax) {
                rec.t = root1;
                rec.poi = r.at(rec.t);
                rec.N = (rec.poi - center) / radius;
                rec.mat = mat;
                get_sphere_uv(rec.N, rec.u, rec.v);
                return true;
            } 
            if (root2 > tmin && root2 < tmax) {
                rec.t = root2;
                rec.poi = r.at(rec.t);
                rec.N = (rec.poi - center) / radius;
                rec.mat = mat;
                get_sphere_uv(rec.N, rec.u, rec.v);
                return true;
            } 
            return false;
        }
    private:
        static void get_sphere_uv(const vec3& p, float& u, float& v) {
            // let theta be the angle from p up to the positive y axis
            // let phi be the angle on the xz plane from the negative x axis to p
            float theta = acos(-p.y());
            float phi = atan2(-p.z(), p.x()) + pi;
            u = phi / (2*pi); // map u and v to a value between 0 and 1
            v = theta / pi;
        }
};