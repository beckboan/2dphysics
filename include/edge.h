#ifndef EDGE_H
#define EDGE_H

#include "common.h"
#include "mathfuncs.h"
#include "shape.h"

struct Edge : public Shape {
  Edge(vec2d s, vec2d e);

  void createAABB();
  ShapeType getType() const;
  std::string getName() const;
  void calculateMassProperties(float density);

  const float edge_radius = polygonRadius;

  // Getters/Setters

  vec2d start_vertex;
  vec2d end_vertex;
  vec2d centroid;
};

#endif
