#include <iostream>
#include "vec2d.h"

//Vector Methods//

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

//Other Vector Functions

//Dot Product

float dp(vec2d& vec1, vec2d& vec2)
{
    return (vec1.x * vec2.x) + (vec1.y * vec2.y);
}

float cp(vec2d& vec1, vec2d& vec2)
{
    return (vec1.x * vec2.y) - (vec1.y * vec2.x);
}