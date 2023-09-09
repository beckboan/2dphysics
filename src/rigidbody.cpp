#include "rigidbody.h"
#include "shape.h"

RigidBody::RigidBody(Shape* shape, vec2d position) : shape(shape->Clone()), position(position) {
    shape->body = this;
    velocity.assign(0,0);
    angular_velocity = 0;
    torque = 0;
    rotation = 0;
    force.assign(0,0);
    static_friction = 0.3f;
    dynamic_friction = 0.2f;
    restitution = 0.2f;
    r,g,b = 120; // TEMP COLORS 
}

void RigidBody::applyForce(const vec2d& other_force) {
    force += other_force;
}

void RigidBody::setBodyStatic() {
    m, I, inv_I, inv_M = 0.0f;
}

//void RigidBody::applyImpulse(const vec2)
