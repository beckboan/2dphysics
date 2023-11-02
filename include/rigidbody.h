#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "mathfuncs.h"
#include <memory>

struct Transform;
struct Shape;

struct RigidBody {
  RigidBody(std::unique_ptr<Shape> &shape_, vec2d &position_, float density_);
  RigidBody(const RigidBody &) = delete;
  RigidBody &operator=(const RigidBody &) = delete;
  ~RigidBody() = default;

  vec2d position;
  vec2d velocity;
  vec2d force;

  float rotation;
  float angular_velocity;
  float torque;

  // Shape Features
  float I;
  float inv_I;
  float m;
  float inv_m;
  float area;
  float density;

  // Friction and Rest
  float static_friction;
  float dynamic_friction;
  float restitution;
  bool hasProperties = 0;
  bool isStatic = 0;

  // Shape Reference
  std::unique_ptr<Shape> shape;

  // Body Color
  int r, g, b;

  // Property Functions
  void rigidIni();
  void setBodyStatic();

  // Getters
  const vec2d &getPosition() const { return position; };

  // Physics Functions
  void move(const vec2d &amount);
  void moveto(const vec2d &position_new);
  void setRotation(float radians);
  void applyForce(vec2d &force, vec2d &point);
  void applyCenterForce(vec2d &force);
  void applyLinearImpulse(vec2d &impulse, vec2d &point);
  void applyCenterLinearImpulse(vec2d &impulse);
};
#endif
