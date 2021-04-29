#pragma once

#include "vec3.h"
#include "img_array.h"
#include <iostream> 

void write_color(int row, int col, std::ostream &out, color pixel_color, float sample_count, img_array &ar) {
    color c(static_cast<int>(255.999 * std::sqrt(pixel_color.x() / sample_count)), 
            static_cast<int>(255.999 * std::sqrt(pixel_color.y() / sample_count)),
            static_cast<int>(255.999 * std::sqrt(pixel_color.z() / sample_count)));
    ar.set_pixel(row, col, c);
}