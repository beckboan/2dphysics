#include "mathfuncs.h"

#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

enum ShapeType {
    Circle = 0, Box = 1
};

class PhysicsObject {

    vec2d position;
    vec2d linear_velocity;
    float rotation;
    float rotational_velocity;
    
public:
    const float mass;
    const float density;
    const float restitution;
    const float area;
    const bool is_static;

    const float radius;
    const float width;
    const float height;

    const ShapeType shape_type;

    PhysicsObject(vec2d& position, float radius, float width, float height, const float density, const float mass, 
    const float restitution, const float area, const bool is_static,
    ShapeType shape_type);

    static bool CreateCircleBody(float radius, vec2d position, float mass, float restitution, bool is_static);
    static bool CreateBoxBody(float width, float height, vec2d position, float density, float restitution, bool is_static);
};


#endif