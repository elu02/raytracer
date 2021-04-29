#include "color.h"
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "hittable.h"
#include "sphere_list.h"
#include "camera.h"
#include "matte.h"
#include "metal.h"
#include "glass.h"
#include "rand.h"
#include "texture.h"

#include <iostream>
#include <cstdlib>
#include <memory>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <thread>

const int inf = 0x3f3f3f3f;
const int image_width = 400;
const int image_height = 200;
const int sample_count = 50;
const int startx = -2.0;
const int starty = -1.0;
const int max_depth = 50;
const int scene_count = 3;

color get_color(const ray& r, std::shared_ptr<sphere_list> sl, int depth) {
    if(depth == max_depth) { 
        return color(0, 0, 0);
    }

    hit_record rec;
    if (sl->hit_test(r, 0.001, inf, rec)) {
        vec3 attenuation;
        ray scatter_ray;
        if (rec.mat->scatter(r, rec, attenuation, scatter_ray)) {
            return attenuation * get_color(scatter_ray, sl, depth + 1);
        } 
        return color(0, 0, 0);
    }
    vec3 unit = unit_vector(r.direction());
    float x = 0.5 * (unit.y() + 1);
    return (1 - x) * vec3(1.0, 1.0, 1.0) + x * vec3(0.5, 0.7, 1.0);
}

int main() {
    std::ofstream out; out.open("output/convert.bat"); out.close();
    // CAMERA
    camera cams[scene_count];
    camera cam_main(pi/2, image_width / image_height, vec3(1, 0, -1), vec3(0, 0, -1), vec3(0, 1, 0));
    camera cam_above(pi/3, image_width / image_height, vec3(2, 2, -1), vec3(0, 0, -1), vec3(0, 1, 0));
    camera cam_left(pi/3, image_width / image_height, vec3(2, 1, 0), vec3(0, 0, -1), vec3(0, 1, 0));
    cams[0] = cam_main;
    cams[1] = cam_above;
    cams[2] = cam_left;

    // SAMPLE TEXTURES
    auto tex1 = std::make_shared<from_image>("images/flushed.jpg");
    auto solid1 = std::make_shared<solid_color>(vec3(0.9, 0.9, 0.9));
    auto solid2 = std::make_shared<solid_color>(vec3(0.9, 0.2, 0.2));
    auto solid3 = std::make_shared<solid_color>(vec3(0.5, 0.9, 0.2));

    // SAMPLE MATERIALS
    auto floor_texture = std::make_shared<matte>(solid1); 
    auto mat1 = std::make_shared<matte>(tex1);
    auto metal_2 = std::make_shared<metal>(vec3(0.9, 0.2, 0.2), 0);
    auto glass_ = std::make_shared<glass>(1.5);

    // SAMPLE SPHERES
    std::shared_ptr<sphere> lst[5];
    lst[0] = std::make_shared<sphere>(vec3(0.0, -100.5, -1.0), 100, floor_texture); 
    lst[1] = std::make_shared<sphere>(vec3(0, 0, -1.0), 0.5, mat1);
    lst[2] = std::make_shared<sphere>(vec3(0, 0, 0), 0.5, glass_);
    lst[3] = std::make_shared<sphere>(vec3(0, 0, 0), -0.45, glass_);
    lst[4] = std::make_shared<sphere>(vec3(0, 0, -2.0), 0.5, metal_2);
    
    // RENDERING 

    auto sl = std::make_shared<sphere_list>(lst, 5);
    for (int scene = 0; scene < scene_count; scene++) {
        out.open("output/out" + std::to_string(scene) + ".ppm");
        out << "P3\n" << image_width << ' ' << image_height << "\n255\n";
        for (int j = image_height-1; j >= 0; --j) {
            for (int i = 0; i < image_width; ++i) {
                color col; 
                for (int k = 0; k < sample_count; k++) {
                    float x = (float) (i + random_float(0, 1)) / (float) image_width;
                    float y = (float) (j + random_float(0, 1)) / (float) image_height;
                    ray r = cams[scene].get_ray(x, y);
                    col += get_color(r, sl, 0);
                }
                write_color(out, col, sample_count);
            }
        }
        out.close();

        // create batch file that uses Image Magick to convert ppm files to jpg files

        /*  out.open("output/convert.bat", std::ios::app);
            out << "magick convert out" << std::to_string(scene) << ".ppm out" << std::to_string(scene) << ".jpg\n"; 
            out.close();  */
        
    }
    // system("cd output && convert.bat"); // runs batch file that converts ppm files to jpg files using Image Magick
}