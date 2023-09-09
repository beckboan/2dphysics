#include <iostream>

#ifndef mathfuncs_H
#define mathfuncs_H

class vec2d {
public: 
    float x;
    float y;

    vec2d();
    vec2d(float x, float y);
    vec2d(const vec2d& vector);

    vec2d& operator=(const vec2d& vec);
    vec2d& operator+=(const vec2d& vec);
    vec2d& operator-=(const vec2d& vec);
    vec2d& operator+=(const float val);
    vec2d& operator-=(const float val);
    vec2d& operator*=(const float val);
    vec2d& operator/=(const float val);
    vec2d operator+(const vec2d& vec) const;
    vec2d operator-(const vec2d& vec) const;
    vec2d operator+(const float val) const;
    vec2d operator-(const float val) const;
    vec2d operator*(const float val) const;
    vec2d operator/(const float val) const;

    void assign(float x, float y);

    float length () const;
};

float dp(vec2d& vec1, vec2d& vec2);
float cp(vec2d& vec1, vec2d& vec2);
float dist( vec2d& vec1, vec2d& vec2);
float distSquared(vec2d& vec1, vec2d& vec2);
float minval(float a, float b);
float maxval(float a, float b);
void clamp(float& val, float min, float max);


#endif