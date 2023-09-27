#include <iostream>
#include "mathfuncs.h"
#include <cmath>

//Vector Methods//

vec2d::vec2d(): x(0), y(0) {}
vec2d::vec2d(float x, float y): x(x), y(y) {}
vec2d::vec2d(const vec2d& vector): x(vector.x), y(vector.y) {}

//Assignment Operators
//Vector Input
vec2d& vec2d::operator=(const vec2d& vec) 
{
    x = vec.x;
    y = vec.y;
    return *this;
}

vec2d& vec2d::operator+=(const vec2d& vec) 
{
    x += vec.x;
    y += vec.y;
    return *this;
}
vec2d& vec2d::operator-=(const vec2d& vec) 
{
    x -= vec.x;
    y -= vec.y;
    return *this;
}

//Float Input
vec2d& vec2d::operator+=(const float val) 
{
    x += val;
    y += val;
    return *this;
}
vec2d& vec2d::operator-=(const float val) 
{
    x -= val;
    y -= val;
    return *this;
}
vec2d& vec2d::operator*=(const float val) 
{
    x *= val;
    y *= val;
    return *this;
}
vec2d& vec2d::operator/=(const float val) 
{
    x /= val;
    y /= val;
    return *this;
}

//Arithmetic Operators
//Vector Input
vec2d vec2d::operator+(const vec2d& vec) const 
{
    return vec2d(x + vec.x, y + vec.y);
}
vec2d vec2d::operator-(const vec2d& vec) const 
{
    return vec2d(x - vec.x, y - vec.y);
}

//Float Input
vec2d vec2d::operator+(const float val) const 
{
    return vec2d(x + val, y + val);
}
vec2d vec2d::operator-(const float val) const 
{
    return vec2d(x - val, y - val);
}
vec2d vec2d::operator*(const float val) const 
{
    return vec2d(x * val, y * val);
}
vec2d vec2d::operator/(const float val) const 
{
    return vec2d(x / val, y / val);
}

float vec2d::length() const  
{
    return std::sqrt((x*x)+(y*y));
}

vec2d vec2d::normalize() 
{
    float len = length();
    return vec2d(x/len,y/len);
}

void vec2d::assign(float x, float y) 
{
    this->x = x;
    this->y = y;
}

vec2d vec2d::negY()
{
    return vec2d(x, -y);
}
