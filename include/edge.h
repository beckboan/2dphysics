#ifndef EDGE
#define EDGE

#include "mathfuncs.h"
#include "shape.h"
#include <iostream>
#include <vector>

struct Edge {
  Edge(vec2d s, vec2d e);

  void createAABB();

  // Getters/Setters

private:
  vec2d start;
  vec2d end;
  AABB aabb = AABB();
};

#endif
