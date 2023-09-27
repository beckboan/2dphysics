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

//Rotation Matrix

mat2d::mat2d() {}
mat2d::mat2d(float radians) 
{
    this->setMatrixRotation(radians);
}
void mat2d::setMatrixRotation(float radians)
{
    float c_val = std::cos(radians);
    float s_val = std::sin(radians);

    row_1[0] = c_val;
    row_1[1] = -1*s_val;
    row_2[0] = s_val;
    row_2[1] = c_val;
}
