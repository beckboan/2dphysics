#ifndef AABB_H
#define AABB_H

#include "mathfuncs.h"
#include <iostream>

struct AABB {
  AABB() {}

  vec2d getMin() const { return min; }
  vec2d getMax() const { return max; }
  void setAABB(vec2d min_, vec2d max_);
  void setMin(vec2d min_);
  void setMax(vec2d max_);
  void setMin(float min_x, float min_y);
  void setMax(float max_x, float max_y);

  void move(const vec2d vec);

private:
  vec2d min; // Bottom Left
  vec2d max; // Top Right
};

inline bool checkAABBOverlap(const AABB &box1, const AABB &box2) {
  return box1.getMin().x <= box2.getMax().x &&
         box1.getMax().x >= box2.getMin().x &&
         box1.getMin().y <= box2.getMax().y &&
         box1.getMax().y >= box2.getMin().y;
}

#endif
