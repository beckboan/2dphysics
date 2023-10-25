#include "polygon.h"
#include <algorithm>
#include <cassert>

// Polygon

// Polygon Sorter
struct GrahamCCWSorter {
  const vec2d &pivot;

  GrahamCCWSorter(const vec2d &pivot_) : pivot(pivot_) {}

  bool operator()(const vec2d &a, const vec2d &b) {
    return findOrientation(a, b, pivot) < 0;
  }
};

Poly::Poly(std::vector<vec2d> &v) {
  // Hull Creation
  std::vector<vec2d> hull;

  // Establish min_x and move to front of verticies
  vec2d min_x = *std::min_element(v.begin(), v.end(), isLeftOf);

  std::swap(v[0], min_x);

  // Sort point ccw around min_x
  std::sort(v.begin() + 1, v.end(), GrahamCCWSorter(v[0]));

  // for (const vec2d& i : v)
  // {
  //     std::cout << "X: " << i.x << "Y: " << i.y << std::endl;
  // }

  hull.push_back(v[0]);
  hull.push_back(v[1]);
  hull.push_back(v[2]);

  for (unsigned int i = 3; i < v.size(); i++) {
    vec2d top = hull.back();
    hull.pop_back();
    while (findOrientation(hull.back(), top, v[i]) >= 0) {
      top = hull.back();
      hull.pop_back();
    }
    hull.push_back(top);
    hull.push_back(v[i]);
  }

  vertex_count = hull.size();

  assert(vertex_count > 2 && vertex_count <= max_poly_count &&
         "Vertex list size out of bounds");

  for (unsigned int i = 0; i < vertex_count; i++) {
    vertex_list.push_back(hull[i]);
    // std::cout << "X: " << hull[i].x << "Y: " << hull[i].y << std::endl;
  }

  calculatePolyNormals();
}

// Poly::Poly(float radius, int side_number)
// {
//     assert(side_number > 2 && side_number <= max_poly_count && "Vertex list
//     size out of bounds");

// }

Poly::Poly(float width, float height) : vertex_count(4) {
  vertex_list.emplace_back(-width / 2, -height / 2);
  vertex_list.emplace_back(width / 2, -height / 2);
  vertex_list.emplace_back(width / 2, height / 2);
  vertex_list.emplace_back(-width / 2, height / 2);
  normals.emplace_back(0, -1); // v
  normals.emplace_back(1, 0);  // ->
  normals.emplace_back(0, 1);  // ^
  normals.emplace_back(-1, 0); // <-
}

Shape::ShapeType Poly::getType() const { return ShapeType::Poly; }

std::string Poly::getName() const { return "Poylgon"; }

// Using triangulation of the polygon to get its area/centroid/inertia
void Poly::calculateMassProperties(float density) {
  vec2d centroid(0, 0);
  float area = 0;
  float I = 0;
  float k_c = 1.0 / 3.0;
  for (unsigned int i = 0; i < vertex_count; i++) {
    vec2d p1 = vertex_list[i];
    unsigned int i2 = i + 1 < vertex_count ? i + 1 : 0;
    vec2d p2 = vertex_list[i2];

    // Calculate parallelogram area and divide by two for triangle area
    float p_area = cp(p1, p2);
    float t_area = 0.5 * p_area;
    area += t_area;

    // Calc Inertia
    float t_I = t_area * (dp(p1, p1) + dp(p2, p2) + dp(p1, p2)) / 6;

    // Calculate triangle center and average w/ area
    centroid += (p1 + p2) * k_c * t_area;

    I += t_I;
  }

  I *= density;
  centroid *= 1.0 / area;
  std::shared_ptr<RigidBody> body_ref = body.lock();
  vec2d position = body_ref->position;

  // std::cout << "X: " << centroid.x << "Y: " << centroid.y << std::endl;
  for (unsigned int i = 0; i < vertex_count; i++) {
    vertex_list[i] -= centroid;
    // std::cout << "X: " << vertex_list[i].x << "Y: " << vertex_list[i].y <<
    // std::endl;
  }

  body_ref->area = area;
  body_ref->m = area * density;
  body_ref->inv_m = (body_ref->m > 0) ? 1.0 / body_ref->m : 0;
  body_ref->I = I;
  body_ref->I = (body_ref->I > 0) ? 1.0 / body_ref->I : 0;
}

void Poly::createAABB() {
  // Multiple by rotation vector for new points.
  vec2d start = rotation->mul(vertex_list[0]);
  float max_x = start.x;
  float max_y = start.y;
  float min_x = start.x;
  float min_y = start.y;

  // Find bounds of AABB
  for (unsigned int i = 0; i < vertex_count; i++) {
    vec2d point = rotation->mul(vertex_list[i]);
    float x = point.x;
    float y = point.y;

    if (x > max_x) {
      max_x = x;
    }
    if (y > max_y) {
      max_y = y;
    }
    if (x < min_x) {
      min_x = x;
    }
    if (y < min_y) {
      min_y = y;
    }
  }

  std::shared_ptr<RigidBody> body_temp = body.lock();
  float position_x = body_temp->position.x;
  float position_y = body_temp->position.y;
  // std::cout << centroid.x << centroid.y << std::endl;
  aabb.setMax(position_x + max_x, position_y + max_y);
  aabb.setMin(position_x + min_x, position_y + min_y);
}
void Poly::calculatePolyNormals() {
  normals.clear();
  assert(vertex_count > 2 && vertex_count < max_poly_count &&
         "Vertex count out of bounds");
  for (unsigned int i = 0; i < vertex_count; i++) {
    vec2d face = vertex_list[(i + 1) % vertex_count] - vertex_list[i];
    normals.push_back(vec2d(face.y, -face.x).normalize());
  }
}
