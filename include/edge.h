#ifndef EDGE
#define EDGE

#include "mathfuncs.h"
#include "shape.h"
#include <iostream>
#include <vector>

struct Edge : public Shape {
  Edge(vec2d s, vec2d e);

  ShapeType getType() const;
  std::string getName() const;
  void calculateMassProperties(float density);
  void createAABB();

  // Getters/Setters

private:
  vec2d start;
  vec2d end;
};

#endif
