#pragma once
#include <math.h>

namespace GLES2{

struct vec4{
    vec4()
        :r(1), g(1), b(1), a(1){
    }

    vec4(float r, float g, float b, float a)
        :r(r), g(g), b(b), a(a){
    }
    float r;
    float g;
    float b;
    float a;
};

struct vec3{
    vec3()
        :x(0), y(0), z(0){
    }
    vec3(float x, float y, float z)
        :x(x), y(y), z(z){
    }
    float x;
    float y;
    float z;

    vec3& operator=(vec4& vec){
        x = vec.r;
        y = vec.g;
        z = vec.b;
        return *this;
    }

    vec3 operator + (const vec3& vec){
        return vec3(x+vec.x, y+vec.y, z+vec.z);
    }

    float dotProduct(const vec3& vec) const {
        return x * vec.x + y * vec.y + z * vec.z;
    }
    vec3 crossProduct(vec3& vec)const{
        return vec3(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x);
    }
    vec3 operator-(vec3 vec) const{
        return vec3(x - vec.x, y - vec.y, z-vec.z);
    }
    void normalise(){
        float l = sqrt(x*x + y*y + z*z);
        if(l != 0){
            float inverseLength = 1.0f/l;
            x *= inverseLength;
            y *= inverseLength;
            z *= inverseLength;
        }
    }
};

struct vec2{
    float s;
    float t;
};

}
