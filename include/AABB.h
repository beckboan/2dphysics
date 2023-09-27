#ifndef AABB_H
#define AABB_H

#include "mathfuncs.h"
#include <iostream>

struct AABB
{
    AABB() {}

    vec2d getMin() const {return min;}
    vec2d getMax() const {return max;}
    void setAABB(vec2d min_, vec2d max_);
    void setMin(vec2d min_);
    void setMax(vec2d max_);
    void setMin(float min_x, float min_y);
    void setMax(float max_x, float max_y);

    private:
    vec2d min; //Bottom Left
    vec2d max; //Top Right
};

inline bool checkAABBOverlap(const AABB& box1, const AABB& box2) 
{
    return true;
}

#endif