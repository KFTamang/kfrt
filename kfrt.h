#pragma once

#include <memory>
#include <cmath>
#include <limits>
#include <cstdlib>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degrees_to_radians(double degrees){
    return degrees * pi / 180.0;
}

inline double random_double(){
    return rand() / (1.0 * RAND_MAX + 1);
}

inline double random_double(double min, double max){
    return min + (max - min) * random_double(); 
}

inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

#include "vec3.h"
#include "ray.h"
