#include "AABB.h"

[[maybe_unused]] void AABB::setAABB(const vec2d &min_, const vec2d &max_) {
    min = min_;
    max = max_;
}
[[maybe_unused]] void AABB::setMin(const vec2d &min_) { min = min_; }
[[maybe_unused]] void AABB::setMax(const vec2d &max_) { max = max_; }
void AABB::setMin(float min_x, float min_y) { min.assign(min_x, min_y); }
void AABB::setMax(float max_x, float max_y) { max.assign(max_x, max_y); }

[[maybe_unused]] void AABB::move(const vec2d &vec) {
    min.x += vec.x;
    max.x += vec.x;
    min.y += vec.y;
    max.y += vec.y;
}
