#include "rigidbody.h"
#include "shape.h"
#include <iostream>

RigidBody::RigidBody(std::unique_ptr<Shape> &shape_, vec2d &position_,
                     float density_)
    : shape(std::move(shape_)), density(density_) {
  position = position_;
  velocity.assign(0, 0);
  angular_velocity = 0;
  torque = 0;
  rotation = 0;
  force.assign(0, 0);
  static_friction = 0.3f;
  dynamic_friction = 0.2f;
  restitution = 0.2f;
  r = 120;
  g = 120;
  b = 120;
}

// Property Functions
void RigidBody::rigidIni() {
  shape->calculateMassProperties(density);
  shape->createAABB();
  hasProperties = true;
}

void RigidBody::setBodyStatic() {
  isStatic = 1;
  m = 0.0f;
  I = 0.0f;
  inv_I = 0.0f;
  inv_m = 0.0f;
}

// Getters

// Physics Functions
void RigidBody::move(const vec2d &amount) { position += amount; }

void RigidBody::moveto(const vec2d &position_new) { position = position_new; }

void RigidBody::setRotation(float radians) {
  rotation = radians;
  shape->setSpaceOrientation(radians);
}

void RigidBody::applyForce(vec2d &other_force, vec2d &point) {
  force += other_force;
  torque += cp(point, other_force);
}

void RigidBody::applyCenterForce(vec2d &other_force) { force += other_force; }

void RigidBody::applyLinearImpulse(vec2d &impulse, vec2d &point) {
  velocity += impulse * inv_m;
  angular_velocity += inv_I * cp(point, impulse);
}

void RigidBody::applyCenterLinearImpulse(vec2d &impulse) {
  velocity += impulse * inv_m;
}
