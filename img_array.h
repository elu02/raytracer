#pragma once
#include "color.h"

#include <stdio.h>
#include <stdlib.h>

class img_array {
    public:
        img_array(int w, int h) {
            width = w;
            height = h;
            data = (unsigned char*) malloc(width * height * 3 * sizeof(unsigned char));
        }

        ~img_array() {
            free(data);
        }

        void set_pixel(int row, int col, color c) {
            data[3 * (row * width + col)] = c.x();
            data[3 * (row * width + col) + 1] = c.y();
            data[3 * (row * width + col) + 2] = c.z();
        }
        
        void print(std::ostream &out) {
            for (int j = height - 1; j >= 0; j--) {
                for (int i = 0; i < width; i++) {
                    out << (int)data[3 * (j * width + i)] << ' '
                        << (int)data[3 * (j * width + i) + 1] << ' ' 
                        << (int)data[3 * (j * width + i) + 2] << '\n';
                }
            }
        }
    
    private:
        int width, height;
        unsigned char *data;
};