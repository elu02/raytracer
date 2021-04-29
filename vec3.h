#pragma once

#include <cmath>
#include <iostream>

class vec3 {
    public: 
        float coords[3];
        vec3() : coords{0, 0, 0} {}
        vec3(float x, float y, float z) {
            coords[0] = x;
            coords[1] = y;
            coords[2] = z;
        }
        float x() const { return coords[0]; }
        float y() const { return coords[1]; }
        float z() const { return coords[2]; }
    
        vec3 operator-() const { return vec3(-coords[0], -coords[1], -coords[2]); }
        float operator[](int i) const { return coords[i]; }
        float& operator[](int i) { return coords[i]; }

        vec3& operator+=(const vec3 &v) {
            coords[0] += v.coords[0];
            coords[1] += v.coords[1];
            coords[2] += v.coords[2];
            return *this;
        }
        vec3& operator*=(const float t) {
            coords[0] *= t;
            coords[1] *= t;
            coords[2] *= t;
            return *this;
        }
        vec3& operator/=(const float t) {
            return *this *= 1/t;
        }
        float length() const {
            return std::sqrt(coords[0]*coords[0] + coords[1]*coords[1] + coords[2]*coords[2]);
        }
};

typedef vec3 color;

inline std::ostream& operator<<(std::ostream &out, const vec3 &v) {
    return out << v.coords[0] << ' ' << v.coords[1] << ' ' << v.coords[2];
}

inline vec3 operator+(const vec3 &u, const vec3 &v) {
    return vec3(u.coords[0] + v.coords[0], u.coords[1] + v.coords[1], u.coords[2] + v.coords[2]);
}

inline vec3 operator-(const vec3 &u, const vec3 &v) {
    return vec3(u.coords[0] - v.coords[0], u.coords[1] - v.coords[1], u.coords[2] - v.coords[2]);
}

inline vec3 operator*(const vec3 &u, const vec3 &v) {
    return vec3(u.coords[0] * v.coords[0], u.coords[1] * v.coords[1], u.coords[2] * v.coords[2]);
}

inline vec3 operator*(float t, const vec3 &v) {
    return vec3(t*v.coords[0], t*v.coords[1], t*v.coords[2]);
}

inline vec3 operator*(const vec3 &v, float t) {
    return t * v;
}

inline vec3 operator/(vec3 v, float t) {
    return (1/t) * v;
}

inline float dot(const vec3 &u, const vec3 &v) {
    return u.coords[0] * v.coords[0]
         + u.coords[1] * v.coords[1]
         + u.coords[2] * v.coords[2];
}

inline vec3 cross(const vec3 &u, const vec3 &v) {
    return vec3(u.coords[1] * v.coords[2] - u.coords[2] * v.coords[1],
                u.coords[2] * v.coords[0] - u.coords[0] * v.coords[2],
                u.coords[0] * v.coords[1] - u.coords[1] * v.coords[0]);
}

inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}