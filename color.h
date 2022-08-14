#pragma once
#include "kfrt.h"
#include "vec3.h"

#include <iostream>

void write_color(std::ostream &out, Color pixel_color, int sample_per_pixel){
    auto r = pixel_color.x();
    auto b = pixel_color.y();
    auto g = pixel_color.z();

    // divide with number of samples
    r *= 1.0/sample_per_pixel;
    b *= 1.0/sample_per_pixel;
    g *= 1.0/sample_per_pixel;

    // gamma correction with gamma=2.0
    r = sqrt(r);
    b = sqrt(b);
    g = sqrt(g);

    out << static_cast<int>(255.999 * clamp(r, 0.0, 0.999)) << " "
        << static_cast<int>(255.999 * clamp(b, 0.0, 0.999)) << " "
        << static_cast<int>(255.999 * clamp(g, 0.0, 0.999)) << "\n";
}