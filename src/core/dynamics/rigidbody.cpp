#include "rigidbody.h"
#include "shape.h"
#include <iostream>

RigidBody::RigidBody(std::unique_ptr<Shape> &shape_, vec2d &position_, float density_) : shape(std::move(shape_)),
                                                                                         density(density_) {
    position = position_;
    velocity.assign(0, 0);
    angular_velocity = 0;
    torque = 0;
    rotation = 0;
    force.assign(0, 0);
    static_friction = 0.5f;
    dynamic_friction = 0.3f;
    restitution = 0.2f;
    r = 255;
    g = 255;
    b = 255;
}

// Property Functions
void RigidBody::rigidIni() {
    shape->calculateMassProperties(density);
    shape->createAABB();
    hasProperties = true;
}

void RigidBody::setBodyStatic() {
    isStatic = true;
    m = 0.0f;
    I = 0.0f;
    inv_I = 0.0f;
    inv_m = 0.0f;
}

void RigidBody::setRGB(int red, int green, int blue) {
    r = red;
    g = green;
    b = blue;
}

// Getters

std::array<int, 3> RigidBody::getRGB() const { return {r, g, b}; }

// Physics Functions
[[maybe_unused]] void RigidBody::move(const vec2d &amount) { position += amount; }

[[maybe_unused]] void RigidBody::moveto(const vec2d &position_new) { position = position_new; }

void RigidBody::setRotation(float radians) {
    rotation = radians;
    shape->setSpaceOrientation(radians);
}

[[maybe_unused]] void RigidBody::applyForce(vec2d &other_force, vec2d &point) {
    force += other_force;
    torque += cp(point, other_force);
    //    std::cout << point.x << " " << point.y << std::endl;
}

[[maybe_unused]] void RigidBody::applyCenterForce(vec2d &other_force) { force += other_force; }

void RigidBody::applyLinearImpulse(vec2d &impulse, vec2d &point) {
    velocity += impulse * inv_m;
    // std::cout << point.x << " " << point.y << std::endl;
    angular_velocity += inv_I * cp(point, impulse);
}

[[maybe_unused]] void RigidBody::applyCenterLinearImpulse(vec2d &impulse) { velocity += impulse * inv_m; }
