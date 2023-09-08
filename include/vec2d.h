#include <iostream>

#ifndef VEC2D_H
#define VEC2D_H

class vec2d {
public: 
    float x;
    float y;

    vec2d(): x(0), y(0) {}
    vec2d(float x, float y): x(x), y(y) {}
    vec2d(const vec2d& vector): x(vector.x), y(vector.y) {std::cout << "Copy Created" <<std::endl;}

    //Overloading operators following operator structure from https://en.cppreference.com/w/cpp/language/operators

    //Assignment Operators
    //Vector Input
    vec2d& operator=(const vec2d& vec);
    vec2d& operator+=(const vec2d& vec);
    vec2d& operator-=(const vec2d& vec);
    //Float Input
    vec2d& operator+=(const float val);
    vec2d& operator-=(const float val);
    vec2d& operator*=(const float val);
    vec2d& operator/=(const float val);

    //Arithmetic Operators
    //Vector Input
    vec2d operator+(const vec2d& vec) const;
    vec2d operator-(const vec2d& vec) const;
    //Float Input
    vec2d operator+(const float val) const;
    vec2d operator-(const float val) const;
    vec2d operator*(const float val) const;
    vec2d operator/(const float val) const;
};

float dp(vec2d& vec1, vec2d& vec2);

#endif