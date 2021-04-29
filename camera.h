#pragma once

#include "ray.h"

#include <iostream>

class camera { 
    private:
        float v_fov, aspect_ratio;
        vec3 origin;
        vec3 bot_left, shift_horiz, shift_vert;

    public: 
        camera () {};
        camera(float vfov, float ar, vec3 orig, vec3 point_to, vec3 v_up) {
            origin = orig;
            float h = 2 * tan(vfov / 2);
            float w = ar * h;

            // establish new axis where z axis points towards "point_to", from the camera origin
            vec3 e_z = unit_vector(origin - point_to);
            vec3 e_x = unit_vector(cross(v_up, e_z));
            vec3 e_y = unit_vector(cross(e_z, e_x));


            bot_left = origin - e_x * w / 2 - e_y * h / 2 - e_z;
            shift_horiz = w * e_x;
            shift_vert = h * e_y;
        }

        ray get_ray(float x, float y) {
            return ray(origin, bot_left + x * shift_horiz + y * shift_vert - origin);
        }
};