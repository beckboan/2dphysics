#include <iostream>

class vec2d {
public: 
    float x;
    float y;

    vec2d(): x(0), y(0) {}
    vec2d(float x, float y): x(x), y(y) {}
    vec2d(const vec2d& vector): x(vector.x), y(vector.y) {}

    

};