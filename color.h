#pragma once
#include "kfrt.h"
#include "vec3.h"

#include <iostream>

void write_color(std::ostream &out, Color pixel_color, int sample_per_pixel){
    auto r = pixel_color.x();
    auto b = pixel_color.y();
    auto g = pixel_color.z();

    r *= 1.0/sample_per_pixel;
    b *= 1.0/sample_per_pixel;
    g *= 1.0/sample_per_pixel;

    out << static_cast<int>(255.999 * clamp(r, 0.0, 0.999)) << " "
        << static_cast<int>(255.999 * clamp(b, 0.0, 0.999)) << " "
        << static_cast<int>(255.999 * clamp(g, 0.0, 0.999)) << "\n";
}