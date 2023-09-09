#include "mathfuncs.h"
#include <memory>
#include <iostream>

#ifndef RIGIDBODY_H
#define RIGIDBODY_H

struct Shape;

struct RigidBody {
    RigidBody(Shape *shape, vec2d position);

    vec2d position;
    vec2d velocity;
    vec2d force;
    
    float rotation;
    float angular_velocity;
    float torque;
    
    //Shape Features
    float I;
    float inv_I;
    float m; 
    float inv_M;
    float area;

    //Friction and Rest
    float static_friction;
    float dynamic_friction;
    float restitution;

    //Shape Reference
    Shape *shape;

    //Body Color
    int r,g,b;

    void applyForce( const vec2d& force);
    //void applyImpulse( const vec2d& impulse);
    void setBodyStatic();



};
#endif
