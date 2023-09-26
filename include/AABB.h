#ifndef AABB_H
#define AABB_H

#include "mathfuncs.h"

struct AABB
{
    vec2d min; //Bottom Left
    vec2d max; //Top Right
};

inline bool checkAABBOverlap(const AABB& box1, const AABB& box2) 
{
    return true;
}

#endif