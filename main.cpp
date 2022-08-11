#include <iostream>

int main(void){
    const int image_width = 256;
    const int image_height = 256;

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for(int i=0; i<image_height; i++){
        for(int j=0; j<image_width; j++){
            auto r = double(i) / (image_width - 1);
            auto b = double(j) / (image_height - 1);
            auto g = 0.5;

            int ir = static_cast<int>(255.999 * r);
            int ib = static_cast<int>(255.999 * b);
            int ig = static_cast<int>(255.999 * g);
            std::cout << ir << " " << ib << " " << ig << "\n";
        }
    }
    
    return 0;
}