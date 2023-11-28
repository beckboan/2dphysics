#ifndef POLYGON
#define POLYGON

#include "common.h"
#include "mathfuncs.h"
#include "shape.h"
#include <vector>

struct Poly : public Shape {
  Poly(std::vector<vec2d> &verticies); // Normal Poly
  Poly(float width, float height);     // Rectangle Poly
  // Poly(float radius, int side_number); //Regular Polygon (think stop sign)

  ShapeType getType() const;
  std::string getName() const;
  void calculateMassProperties(float density);
  void createAABB();

  // Getters/Setters
  const unsigned int &getVertexCount() const { return vertex_count; }
  const std::vector<vec2d> &getVertexList() const { return vertex_list; }
  const std::vector<vec2d> &getNormals() const { return normals; }

  const float poly_radius = polygonRadius;

private:
  unsigned int vertex_count = 0;
  std::vector<vec2d> vertex_list;
  std::vector<vec2d> normals;
  vec2d centroid;
  void calculatePolyNormals();
};

#endif
