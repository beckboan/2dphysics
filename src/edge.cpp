#include "edge.h"

Edge::Edge(vec2d s, vec2d e) : start_vertex(s), end_vertex(e) {}

void Edge::createAABB() {
  vec2d v1 = rotation->mul(start_vertex);
  vec2d v2 = rotation->mul(end_vertex);
  aabb.setMax(std::max(v1.x, v2.x), std::max(v1.y, v2.y));
  aabb.setMin(std::min(v1.x, v2.x), std::min(v1.y, v2.y));
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
