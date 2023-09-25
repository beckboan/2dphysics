#include "rigidbody.h"
#include "shape.h"
#include <iostream>

RigidBody::RigidBody(std::unique_ptr<Shape>& shape_, vec2d& position_, float density_) : shape(std::move(shape_)), density(density_){
    position = position_;
    shape->setBody(shared_from_this());
    velocity.assign(0,0);
    angular_velocity = 0;
    torque = 0;
    rotation = 0;
    force.assign(0,0);
    static_friction = 0.3f;
    dynamic_friction = 0.2f;
    restitution = 0.2f;
    r,g,b = 120; // TEMP COLORS 
    rigidIni();
}

//Property Functions
void RigidBody::rigidIni() {
    shape->calculateMassProperties(density);
    hasProperties = true;
}

void RigidBody::setBodyStatic() {
    m, I, inv_I, inv_m = 0.0f;
}

//Physics Functions
void RigidBody::move(const vec2d& amount) {
    position+=amount;
}

void RigidBody::moveto(const vec2d& position_new) {
    position=position_new;
}

void RigidBody::setRotation(float radians) {
    rotation = radians;
}

void RigidBody::applyForce(const vec2d& other_force) {}

void RigidBody::applyCenterForce(const vec2d& other_force) {
    force += other_force;
}

void RigidBody::applyLinearImpulse(const vec2d& impulse) {}

void RigidBody::applyCenterLinearImpulse(const vec2d& impulse) {
    velocity += impulse * inv_m;
}

