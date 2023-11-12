#ifndef EDGE
#define EDGE

#include "mathfuncs.h"
#include "shape.h"
#include <iostream>
#include <vector>

struct Edge : public Shape {
  Edge(vec2d s, vec2d e);

  void createAABB();
  ShapeType getType() const;
  std::string getName() const;
  void calculateMassProperties(float density) = 0;

  // Getters/Setters

private:
  vec2d start_vertex;
  vec2d end_vertex;
  AABB aabb = AABB();
};

#endif
