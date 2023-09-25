#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "mathfuncs.h"

struct Transform
{

    vec2d transform_position;
    float sin_theta;
    float cos_theta;

    Transform(vec2d& position, float angle);
    Transform(float x, float y, float angle);
};


#endif