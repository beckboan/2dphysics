#include <iostream>
#include "mathfuncs.h"
#include <cmath>

//Vector Methods//

vec2d::vec2d(): x(0), y(0) {}
vec2d::vec2d(float x, float y): x(x), y(y) {}
vec2d::vec2d(const vec2d& vector): x(vector.x), y(vector.y) {}

//Assignment Operators
//Vector Input
vec2d& vec2d::operator=(const vec2d& vec) {
    x = vec.x;
    y = vec.y;
    return *this;
}

vec2d& vec2d::operator+=(const vec2d& vec) {
    x += vec.x;
    y += vec.y;
    return *this;
}
vec2d& vec2d::operator-=(const vec2d& vec) {
    x -= vec.x;
    y -= vec.y;
    return *this;
}

//Float Input
vec2d& vec2d::operator+=(const float val) {
    x += val;
    y += val;
    return *this;
}
vec2d& vec2d::operator-=(const float val) {
    x -= val;
    y -= val;
    return *this;
}
vec2d& vec2d::operator*=(const float val) {
    x *= val;
    y *= val;
    return *this;
}
vec2d& vec2d::operator/=(const float val) {
    x /= val;
    y /= val;
    return *this;
}

//Arithmetic Operators
//Vector Input
vec2d vec2d::operator+(const vec2d& vec) const {
    return vec2d(x + vec.x, y + vec.y);
}
vec2d vec2d::operator-(const vec2d& vec) const {
    return vec2d(x - vec.x, y - vec.y);
}

//Float Input
vec2d vec2d::operator+(const float val) const {
    return vec2d(x + val, y + val);
}
vec2d vec2d::operator-(const float val) const {
    return vec2d(x - val, y - val);
}
vec2d vec2d::operator*(const float val) const {
    return vec2d(x * val, y * val);
}
vec2d vec2d::operator/(const float val) const {
    return vec2d(x / val, y / val);
}

float vec2d::length() const  {
    return std::sqrt((x*x)+(y*y));
}

vec2d vec2d::normalize() {
    float len = length();
    return vec2d(x/len,y/len);
}

void vec2d::assign(float x, float y) {
    this->x;
    this->y;
}

//Other Vector Functions

//Dot Product
float dp(vec2d& vec1, vec2d& vec2) {
    return (vec1.x * vec2.x) + (vec1.y * vec2.y);
}

//Cross Product (In 2D Space)
float cp(vec2d& vec1, vec2d& vec2) {
    return (vec1.x * vec2.y) - (vec1.y * vec2.x);
}

//Distance between
float dist( vec2d& vec1, vec2d& vec2) {
    vec2d d(vec1.x-vec2.x, vec1.y-vec2.y);
    return d.length();
}

//Distance between squared for reduced sqrt ops
float distSquared(vec2d& vec1, vec2d& vec2) {
    vec2d d(vec1.x-vec2.x, vec1.y-vec2.y);
    return (d.x*d.x)+(d.y*d.y);
}

float minval(float a, float b)
{
    return a < b ? a : b;
}

float maxval(float a, float b)
{
    return a > b ? a : b;
}

void clamp(float& val, float min, float max) {
    val = maxval(min, minval(val, max));
}


float findOrientation(const vec2d& p1, const vec2d& p2, const vec2d& p) {
    const float val = (p2.y- p1.y) * (p.x - p2.x) - (p2.x - p1.x) * (p.y - p2.y);
    if (val > 0) {return 1;} //CW
    else if (val < 0) { return -1;} //CCW
    else return 0; // Collinear
}

bool isLeftOf( const vec2d& p1, const vec2d& p2) {
    return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
}