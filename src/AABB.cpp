#include "AABB.h"

void AABB::setAABB(vec2d min_, vec2d max_) {
  min = min_;
  max = max_;
}
void AABB::setMin(vec2d min_) { min = min_; }
void AABB::setMax(vec2d max_) { max = max_; }
void AABB::setMin(float min_x, float min_y) { min.assign(min_x, min_y); }
void AABB::setMax(float max_x, float max_y) { max.assign(max_x, max_y); }

void AABB::move(const vec2d vec) {
  min.x += vec.x;
  max.x += vec.x;
  min.y += vec.y;
  max.y += vec.y;
}
