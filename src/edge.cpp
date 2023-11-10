#include "edge.h"

Edge::Edge(vec2d s, vec2d e) : start(s), end(e) {}

void Edge::createAABB() {

  aabb.setMax(std::max(start.x, end.x), std::max(start.y, end.y));
  aabb.setMin(std::min(start.x, end.x), std::min(start.y, end.y));
}
