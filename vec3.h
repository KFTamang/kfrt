#pragma once

#include <cmath>
#include <iostream>

using std::sqrt;

class vec3{
    public:
        vec3(): e{0, 0, 0} {}
        vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

        double x() const {return e[0];}
        double y() const {return e[1];}
        double z() const {return e[2];}

        vec3 operator-() const {return vec3(-e[0], -e[1], -e[2]);}
        double operator[](int i) const {return e[i];}
        double& operator[](int i) {return e[i];}

        vec3& operator+=(const vec3 &v){
            e[0] += v[0];
            e[1] += v[1];
            e[2] += v[2];
            return *this;
        }

        vec3& operator*=(const double t){
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        vec3& operator/=(const double t){
            return *this *= (1/t);
        }

        double length(){
            return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
        }

        double length_squared(){
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }

        inline static vec3 random(){
            return vec3(random_double(), random_double(), random_double());
        }

        inline static vec3 random(double min, double max){
            return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
        }

        inline bool is_near_zero(){
            const double s = 1e-8;
            return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
        } 

    private:
        double e[3];
};

// type alias

using Point3 = vec3;
using Color = vec3;

inline std::ostream& operator<<(std::ostream &out, const vec3 &v){
    return out << v[0] << " " << v[1] << " " << v[2];
}

inline vec3 operator+(const vec3 &u, const vec3 &v){
    return vec3(u[0] + v[0], u[1] + v[1], u[2] + v[2]);
}

inline vec3 operator-(const vec3 &u, const vec3 &v){
    return vec3(u[0] - v[0], u[1] - v[1], u[2] - v[2]);
}

inline vec3 operator*(const vec3 &u, const vec3 &v){
    return vec3(u[0] * v[0], u[1] * v[1], u[2] * v[2]);
}

inline vec3 operator*(double t, const vec3 &v){
    return vec3(t * v[0], t * v[1], t * v[2]);
}

inline vec3 operator*(const vec3 &v, double t){
    return t * v;
}

inline vec3 operator/(const vec3 &v, double t){
    return (1/t) * v;
}

inline double dot(const vec3 &u, const vec3 &v){
    return v[0] * u[0] + v[1] * u[1] + v[2] * u[2];
}

inline vec3 cross(const vec3 &u, const vec3 &v){
    return vec3(u[1] * v[2] - u[2] * v[1],
                u[2] * v[0] - u[0] * v[2],
                u[0] * v[1] - u[1] * v[0]);
}

inline vec3 unit_vector(vec3 v){
    return v / v.length();
}


inline vec3 random_in_unit_sphere(){
    return vec3::random(-1, 1);
}

inline vec3 random_unit_vector(){
    return unit_vector(random_in_unit_sphere());
}

inline vec3 reflect(const vec3& v, const vec3& n){
    return v - 2 * dot(v, n) * n;
}

inline vec3 refract(const vec3& v, const vec3& n, double index_ratio){
    auto cos_theta = fmin(dot(-v, n), 1.0);
    vec3 r_perp = index_ratio * (v + cos_theta * n);
    vec3 r_parallel = -sqrt(fabs(1.0 - r_perp.length_squared())) * n;
    return r_perp + r_parallel;
}