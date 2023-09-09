#include "vec2d.h"

#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

struct physicsObject {
    vec2d position;
    vec2d velocity;
    vec2d force;
    float mass;
};

#endif