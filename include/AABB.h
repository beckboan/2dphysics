#ifndef AABB_H
#define AABB_H

#include "mathfuncs.h"

struct AABB
{
private:
    vec2d min; //Bottom Left
    vec2d max; //Top Right

public: 
};

inline bool checkAABBOverlap(const AABB& box1, const AABB& box2) 
{
}

#endif