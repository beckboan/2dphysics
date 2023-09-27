#ifndef AABB_H
#define AABB_H

#include "mathfuncs.h"
#include <iostream>

struct AABB
{
    AABB() {}


    vec2d getMin() const {return min;}
    vec2d getMax() const {return max;}

    vec2d min; //Bottom Left
    vec2d max; //Top Right
};

inline bool checkAABBOverlap(const AABB& box1, const AABB& box2) 
{
    return true;
}

#endif