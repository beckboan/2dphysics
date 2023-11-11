#include "edge.h"

Edge::Edge(vec2d s, vec2d e) : start(s), end(e) {}

void Edge::createAABB() {

  aabb.setMax(std::max(start.x, end.x), std::max(start.y, end.y));
  aabb.setMin(std::min(start.x, end.x), std::min(start.y, end.y));
}
Shape::ShapeType Edge::getType() const { return ShapeType::Edge; }

std::string Edge::getName() const { return "Edge"; }

void Edge::calculateMassProperties(float density) {
  std::shared_ptr<RigidBody> body_ref = body.lock();
  body_ref->area = 0;
  body_ref->m = body_ref->area * density;
  body_ref->I = 0;
  body_ref->inv_m = (body_ref->m) ? 1.0f / body_ref->I : 0;
  body_ref->inv_I = (body_ref->I) ? 1.0f / body_ref->I : 0;
}
