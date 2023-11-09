#ifndef EDGE
#define EDGE

#include "mathfuncs.h"
#include "shape.h"
#include <iostream>
#include <vector>

struct Edge : public Shape {
  Edge(std::vector<vec2d> &verticies); // Normal Poly

  ShapeType getType() const;
  std::string getName() const;
  void calculateMassProperties(float density);
  void createAABB();

  // Getters/Setters
  const unsigned int &getVertexCount() const { return vertex_count; }
  const std::vector<vec2d> &getVertexList() const { return vertex_list; }
  const std::vector<vec2d> &getNormals() const { return normals; }

private:
  unsigned int vertex_count = 0;
  std::vector<vec2d> vertex_list;
  std::vector<vec2d> normals;
};

#endif
