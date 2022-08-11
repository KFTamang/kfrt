#include <iostream>
#include "vec3.h"
#include "color.h"

int main(void){
    const int image_width = 256;
    const int image_height = 256;

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for(int i=0; i<image_height; i++){
        std::cerr << "Scanline remaining:" << image_height - i << std::endl;
        for(int j=0; j<image_width; j++){
            auto r = double(i) / (image_width - 1);
            auto b = double(j) / (image_height - 1);
            auto g = 0.5;
            color pixel_color(r, b, g);
            write_color(std::cout, pixel_color);
        }
    }
    std::cerr << "Done\n";
    return 0;
}