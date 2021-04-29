#pragma once

#include "vec3.h"

#define STB_IMAGE_IMPLEMENTATION
#include "external/stb_image.h"

class texture {
    public: 
        virtual color value(float u, float v) const = 0;
};

class solid_color : public texture {
    public:
        solid_color(color col) : c(col) {};

        color value(float u, float v) const override {
            return c;
        } 

    private:
        color c; 
};


class from_image : public texture {
    public:
        int components_per_pixel = 3;
        from_image(const char* file) {
            data = stbi_load(file, &width, &height, &components_per_pixel, components_per_pixel);
            if(!data) {
                std::cerr << "error loading texture image file '" << file << "'\n";  
            }  
        }

        ~from_image() {
            delete data;
        }

        color value(float u, float v) const override {
            int i = (u > 0 ? u * width : 0);
            int j = (v < 1 ? (1 - v) * height : 0);
            i = (i == width ? width - 1 : i);
            j = (j == height ? height - 1: j);
            return color(data[components_per_pixel * i + components_per_pixel * j * width] / 255.0, 
                         data[components_per_pixel * i + components_per_pixel * j * width+ 1] / 255.0, 
                         data[components_per_pixel * i + components_per_pixel * j * width + 2] / 255.0);
        }
    
    private:
        unsigned char *data;
        int width, height;
};