#include "mathfuncs.h"

#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

enum ShapeType {
    Circle = 0, Box = 1
};

class PhysicsObject {
private:
    vec2d position;
    vec2d linear_velocity;
    float rotation;
    float rotational_velocity;
    
public:
    const float mass;
    const float restitution;
    const float area;
    const bool is_static;

    const ShapeType shape_type;

private:
    PhysicsObject(vec2d position, vec2d linear_velocity, float rotation, float rotational_velocity,
    const float mass, const float restitution, const float area, const bool is_static,
    ShapeType shape_type);

public: 
    static bool CreateCircleBody(float radius, float mass, float restitution, bool is_static);
};


#endif