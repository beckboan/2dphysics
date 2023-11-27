#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "rigidbody.h"
#include <memory>

struct Manifold {
  Manifold(std::shared_ptr<RigidBody> A_, std::shared_ptr<RigidBody> B_);

  std::shared_ptr<RigidBody> A;
  std::shared_ptr<RigidBody> B;

  void collisionCaller();
  void solve();
  void applyCollisionImpulse();
  void correctPositions();
  const uint32_t &getContactCount() const { return contact_count; }

private:
  float penetration;
  uint32_t contact_count = 0;
  vec2d normal = vec2d(0, 0);
  vec2d contacts[2] = {vec2d(0, 0), vec2d(0, 0)};
  float e;
  float df;
  float sf;
  bool reverse = false;

  void CirclevsCircle();
  void CirclevsPoly();
  void PolyvsPoly();
  void PolyvsEdge();
  void CirclevsEdge();
  void EdgevsEdge();
};

#endif
