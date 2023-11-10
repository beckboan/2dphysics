#include "edge.h"

Edge::Edge(vec2d s, vec2d e) : start(s), end(e) {}

Shape::ShapeType Edge::getType() const { return ShapeType::Poly; }

std::string Edge::getName() const { return "Poylgon"; }

void Edge::calculateMassProperties(float density) {

  std::shared_ptr<RigidBody> body_ref = body.lock();
  vec2d position = body_ref->position;
  body_ref->area = 0;
  body_ref->m = 0;
  body_ref->inv_m = 0;
  body_ref->I = 0;
  body_ref->inv_I = 0;
}

void Edge::createAABB() {

  aabb.setMax(0, 0);
  aabb.setMin(0, 0);
}
