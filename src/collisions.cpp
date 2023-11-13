#include "collisions.h"
#include "circle.h"
#include "edge.h"
#include "mathfuncs.h"
#include "polygon.h"
#include "shape.h"
#include <cstdint>

Manifold::Manifold(std::shared_ptr<RigidBody> A_, std::shared_ptr<RigidBody> B_)
    : A(A_), B(B_) {
  // std::cout << "Manifold Created" << std::endl;
  e = std::min(A->restitution, B->restitution);
  df = std::sqrt(A->dynamic_friction * B->dynamic_friction);
  sf = std::sqrt(A->static_friction * B->dynamic_friction);
}

void Manifold::collisionCaller() {
  Shape::ShapeType A_type = A->shape->getType();
  Shape::ShapeType B_type = B->shape->getType();

  if (A_type == Shape::ShapeType::Poly && B_type == Shape::ShapeType::Poly) {
    PolyvsPoly();
  } else if (A_type == Shape::ShapeType::Poly &&
             B_type == Shape::ShapeType::Circle) {
    reverse = true;
    CirclevsPoly();
  } else if (A_type == Shape::ShapeType::Circle &&
             B_type == Shape::ShapeType::Poly) {
    CirclevsPoly();
  } else if (A_type == Shape::ShapeType::Circle &&
             B_type == Shape::ShapeType::Circle) {
    CirclevsCircle();
  } else if (A_type == Shape::ShapeType::Edge &&
             B_type == Shape::ShapeType::Edge) {
    EdgevsEdge();
  } else if (A_type == Shape::ShapeType::Poly &&
             B_type == Shape::ShapeType::Edge) {
    PolyvsEdge();
  } else if (A_type == Shape::ShapeType::Edge &&
             B_type == Shape::ShapeType::Poly) {
    reverse = true;
    PolyvsEdge();
  } else if (A_type == Shape::ShapeType::Circle &&
             B_type == Shape::ShapeType::Edge) {
    CirclevsEdge();
  } else if (A_type == Shape::ShapeType::Edge &&
             B_type == Shape::ShapeType::Circle) {
    reverse = true;
    CirclevsEdge();
  }
}

void Manifold::CirclevsCircle() {
  // std::cout << "Circle Collision" << std::endl;
  Circle *C1 = dynamic_cast<Circle *>(A->shape.get());
  Circle *C2 = dynamic_cast<Circle *>(B->shape.get());

  float dist_sq = distSquared(A->position, B->position);

  float radii = C1->radius + C2->radius;

  // Return if circles are further than sum of radii - using
  // dist_sq for faster computation of this case (no sqrt)

  if (dist_sq > (radii * radii)) {
    contact_count = 0;
    return;
  }

  float distance = dist(A->position, B->position);

  contact_count = 1;

  // If distance is 0, the circles are directly overlapping and their
  // contact is at the center of A or B (same thing)

  if (distance == 0.0f) {
    penetration = C1->radius;
    contacts[0] = A->position;
    normal.assign(1, 0);
  }

  else {
    normal = (B->position - A->position).normalize();
    penetration = radii - distance;
    contacts[0] = normal * C1->radius + A->position;
  }
}

void Manifold::CirclevsPoly() {
  std::cout << "Circle/Polygon Collision" << std::endl;
  if (reverse == true) {
    Circle *C = dynamic_cast<Circle *>(B->shape.get());
    Poly *P = dynamic_cast<Poly *>(A->shape.get());
  } else {
    Circle *C = dynamic_cast<Circle *>(A->shape.get());
    Poly *P = dynamic_cast<Poly *>(B->shape.get());
  }
}

void Manifold::PolyvsEdge() {

  std::cout << "Poly/Edge Collision" << std::endl;
  if (reverse == true) {
    Poly *P = dynamic_cast<Poly *>(B->shape.get());
    Edge *E = dynamic_cast<Edge *>(A->shape.get());
  } else {
    Poly *P = dynamic_cast<Poly *>(A->shape.get());
    Edge *E = dynamic_cast<Edge *>(B->shape.get());
  }
}
void Manifold::CirclevsEdge() {

  std::cout << "Circle/Edge Collision" << std::endl;
  if (reverse == true) {
    Circle *C = dynamic_cast<Circle *>(B->shape.get());
    Edge *E = dynamic_cast<Edge *>(A->shape.get());
  } else {
    Circle *C = dynamic_cast<Circle *>(A->shape.get());
    Edge *E = dynamic_cast<Edge *>(B->shape.get());
  }
}
void Manifold::EdgevsEdge() {

  Edge *E1 = dynamic_cast<Edge *>(A->shape.get());
  Edge *E2 = dynamic_cast<Edge *>(B->shape.get());
}

void Manifold::solve() {
  for (auto c : contacts) {
    // Calculate vector from COM to contact
    vec2d a_con = c - A->position;
    vec2d b_con = c - B->position;

    // Compute relative velocity
    vec2d r_vel = B->velocity + cp(B->angular_velocity, b_con) - A->velocity -
                  cp(A->angular_velocity, a_con);

    // Computer relative velocity along normal
    float contact_vel = dp(r_vel, normal);

    // Only solve if objects are moving towards each other
    if (contact_vel > 0)
      return;

    // Method from Chris Hecker's 3D Dynamics in Game Developer Maganize 1997
    float acn = cp(a_con, normal);
    float bcn = cp(b_con, normal);

    float inv_mass_sum =
        A->inv_m + B->inv_m + (acn * acn) * A->inv_I + (bcn * bcn) * B->inv_I;

    float j = (-(e + 1.0f) * contact_vel) / inv_mass_sum;

    vec2d imp = normal * j;
    vec2d imp_neg = imp * -1;
    B->applyLinearImpulse(imp, b_con);
    A->applyLinearImpulse(imp_neg, a_con);
  }
}

void Manifold::PolyvsPoly() {
  std::cout << "Polygon Collision" << std::endl;
  Poly *P1 = dynamic_cast<Poly *>(A->shape.get());
  Poly *P2 = dynamic_cast<Poly *>(B->shape.get());
}

float findAOLP(uint16_t &face, Poly *poly1, Poly *poly2) {
  float max_dist = std::numeric_limits<float>::min();
  uint16_t max_index;

  std::vector<vec2d> A_normals = poly1->getNormals();
  std::vector<vec2d> B_normals = poly2->getNormals();

  face = max_index;
  return max_dist;
}
