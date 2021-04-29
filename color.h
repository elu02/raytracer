#pragma once

#include "vec3.h"
#include <iostream> 

void write_color(std::ostream &out, color pixel_color, float sample_count) {
    out << static_cast<int>(255.999 * std::sqrt(pixel_color.x() / sample_count)) << ' '
        << static_cast<int>(255.999 * std::sqrt(pixel_color.y() / sample_count)) << ' '
        << static_cast<int>(255.999 * std::sqrt(pixel_color.z() / sample_count)) << '\n';
}