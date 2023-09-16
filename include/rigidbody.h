#include "mathfuncs.h"
#include <memory>
#include <iostream>

#ifndef RIGIDBODY_H
#define RIGIDBODY_H

struct Shape;

struct RigidBody {
    RigidBody(std::unique_ptr<Shape>& shape_, vec2d& position_, float density_);
    RigidBody(const RigidBody&) = delete;
    RigidBody& operator=(const RigidBody&) = delete;
    ~RigidBody() = default;

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
    float inv_m;
    float area;
    float density;

    //Friction and Rest
    float static_friction;
    float dynamic_friction;
    float restitution;
    bool hasProperties = 0;

    //Shape Reference
    std::unique_ptr<Shape> shape;

    //Body Color
    int r,g,b;

    void applyForce( const vec2d& force);
    //void applyImpulse( const vec2d& impulse);
    void setBodyStatic();
    // void rigidIni();


};
#endif
