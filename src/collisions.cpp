#include "collisions.h"
#include "circle.h"
#include "common.h"
#include "edge.h"
#include "mathfuncs.h"
#include "shape.h"
#include <assert.h>
#include <cfloat>
#include <cmath>
#include <cstdint>
#include <iostream>

Manifold::Manifold(std::shared_ptr<RigidBody> A_, std::shared_ptr<RigidBody> B_)
    : A(A_), B(B_) {
  // std::cout << "Manifold Created" << std::endl;
  e = std::min(A->restitution, B->restitution);
  df = std::sqrt(A->dynamic_friction * B->dynamic_friction);
  sf = std::sqrt(A->static_friction * B->dynamic_friction);
}

void Manifold::solve() {
  for (uint32_t i = 0; i < contact_count; i++) {
    // Calculate vector from COM to contact
    vec2d a_con = contacts[i] - A->position;
    vec2d b_con = contacts[i] - B->position;

    // std::cout << "Solving" << std::endl;
    // std::cout << a_con.x << " " << a_con.y << std::endl;
    // std::cout << b_con.x << " " << b_con.y << std::endl;
    // std::cout << contacts[i].x << " " << contacts[i].y << std::endl;

    // Compute relative velocity
    vec2d r_vel = B->velocity + cp(B->angular_velocity, b_con) - A->velocity -
                  cp(A->angular_velocity, a_con);

    // std::cout << B->velocity.x << " " << B->velocity.y << std::endl;
    // std::cout << A->velocity.x << " " << A->velocity.y << std::endl;
    // std::cout << A->angular_velocity << " " << B->angular_velocity <<
    // std::endl;

    // Compute relative velocity along normal
    float contact_vel = dp(r_vel, normal);
    // std::cout << contact_vel << std::endl;

    // Only solve if objects are moving towards each other
    if (contact_vel >= 0.0)
      return;

    // Method from Chris Hecker's 3D Dynamics in Game Developer Maganize 1997
    float acn = cp(a_con, normal);
    float bcn = cp(b_con, normal);

    // std::cout << acn << std::endl;
    // std::cout << bcn << std::endl;

    float inv_mass_sum =
        A->inv_m + B->inv_m + (acn * acn) * A->inv_I + (bcn * bcn) * B->inv_I;
    // std::cout << A->inv_I << " " << B->inv_I << std::endl;
    // std::cout << inv_mass_sum << std::endl;

    float j = (-(e + 1.0) * contact_vel) / inv_mass_sum;
    j /= (float)contact_count;

    // std::cout << j << std::endl;
    // std::cout << normal.x << " " << normal.y << std::endl;
    vec2d imp = normal * j;

    // std::cout << imp.x << " " << imp.y << std::endl;

    vec2d imp_neg = -imp;

    // if (std::abs(imp.length() - 0.0) < EPSILON)
    //   return;

    B->applyLinearImpulse(imp, b_con);
    A->applyLinearImpulse(imp_neg, a_con);

    r_vel = B->velocity + cp(B->angular_velocity, b_con) - A->velocity -
            cp(A->angular_velocity, a_con);

    vec2d t = r_vel;
    t += normal * -dp(r_vel, normal);
    t = t.normalize();

    float jt = -dp(r_vel, t);
    jt /= inv_mass_sum;
    jt /= (float)contact_count;

    if (std::abs(jt - 0.0) < EPSILON)
      return;

    vec2d tan_imp;
    if (std::abs(jt) < j * sf) {
      tan_imp = t * jt;
    } else {
      tan_imp = t * j * (-df);
    }

    vec2d tan_imp_neg = -tan_imp;
    // B->applyLinearImpulse(tan_imp, b_con);
    // A->applyLinearImpulse(tan_imp_neg, a_con);
  }
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
    // Edge vs Edge not supported
    return;
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
  std::cout << "Circle Collision" << std::endl;
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
  } else {
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

  RigidBody *circ_bod;
  RigidBody *edge_bod;
  Circle *C;
  Edge *E;

  if (reverse == true) {
    C = dynamic_cast<Circle *>(B->shape.get());
    circ_bod = B.get();
    E = dynamic_cast<Edge *>(A->shape.get());
    edge_bod = A.get();
  } else {
    C = dynamic_cast<Circle *>(A->shape.get());
    circ_bod = A.get();
    E = dynamic_cast<Edge *>(B->shape.get());
    edge_bod = B.get();
  }

  contact_count = 0;

  vec2d center = circ_bod->position;
  center = E->rotation->transpose() * (center - edge_bod->position);

  vec2d s = E->start_vertex;
  vec2d e = E->end_vertex;
  vec2d f = e - s;
}

void Manifold::PolyvsPoly() {
  std::cout << "Poly Collision" << std::endl;
  Poly *P1 = dynamic_cast<Poly *>(A->shape.get());
  Poly *P2 = dynamic_cast<Poly *>(B->shape.get());

  contact_count = 0;
  float total_radius = P1->poly_radius + P2->poly_radius;
  // std::cout << total_radius << std::endl;

  uint32_t face_A = 0;
  float pen_A = findAOLP(face_A, P1, P2, A->position, B->position);
  if (pen_A > total_radius) {
    // std::cout << "No Collision" << std::endl;
    return;
  }
  uint32_t face_B = 0;
  float pen_B = findAOLP(face_B, P2, P1, B->position, A->position);
  if (pen_B > total_radius) {
    // std::cout << "No Collision" << std::endl;
    return;
  }

  // std::cout << pen_A << " " << pen_B << std::endl;
  // std::cout << "Collision Detected" << std::endl;

  Poly *ref;
  Poly *inc;

  uint32_t ref_index;
  bool flip;
  vec2d ref_pos;
  vec2d inc_pos;

  // Bias selection of ref/inc poly taken from box2d
  const float k_tol = 0.1 * linearSlop;

  if (pen_B > pen_A + k_tol) {
    ref = P2;
    ref_pos = B->position;
    inc = P1;
    inc_pos = A->position;
    ref_index = face_B;
    flip = true;
    // std::cout << "Poly B is Ref" << std::endl;
  } else {
    ref = P1;
    ref_pos = A->position;
    inc = P2;
    inc_pos = B->position;
    ref_index = face_A;
    flip = false;
    // std::cout << "Poly A is Ref" << std::endl;
  }

  std::array<vec2d, 2> incident_edge;
  findIncidentFace(incident_edge, ref, inc, inc_pos, ref_index);

  vec2d r_v1 = ref->getVertexList()[ref_index];
  ref_index = ref_index + 1 >= ref->getVertexCount() ? 0 : ref_index + 1;
  vec2d r_v2 = ref->getVertexList()[ref_index];

  // Transform vectors to world space
  r_v1 = ref->rotation->mul(r_v1) + ref_pos;
  r_v2 = ref->rotation->mul(r_v2) + ref_pos;

  // Find side tangent and normalize
  vec2d side_tangent = (r_v2 - r_v1).normalize();
  // std::cout << side_tangent.x << " " << side_tangent.y << std::endl;

  // Find orthogonal
  vec2d side_normal(side_tangent.y, -side_tangent.x);

  // std::cout << side_tangent.x << " " << side_tangent.y << std::endl;

  // Finding front offsets and sides
  float front_offset = dp(side_normal, r_v1);
  float neg_side = -dp(side_tangent, r_v1) + total_radius;
  float pos_side = dp(side_tangent, r_v2) + total_radius;

  if (clipEdges(-side_tangent, neg_side, incident_edge) < 2)
    return;

  if (clipEdges(side_tangent, pos_side, incident_edge) < 2)
    return;

  // Checking for penetration by clipping points
  uint32_t clipped_points = 0;
  float sep = dp(side_normal, incident_edge[0]) - front_offset;
  if (sep <= 0.0) {
    contacts[clipped_points] = incident_edge[0];

    penetration = -sep;
    ++clipped_points;
  } else {
    penetration = 0;
  }

  sep = dp(side_normal, incident_edge[1]) - front_offset;
  if (sep <= 0.0) {
    contacts[clipped_points] = incident_edge[1];

    penetration += -sep;
    ++clipped_points;

    penetration /= clipped_points * 1.0;
  }

  // std::cout << normal.x << " " << normal.y << std::endl;
  contact_count = clipped_points;
  // std::cout << penetration << std::endl;
  normal = flip ? -side_normal : side_normal;
}

// AOLP adapted from Randy Gaul's Impulse Engine and box2d
float findAOLP(uint32_t &face_index, Poly *A, Poly *B, vec2d pos_A,
               vec2d pos_B) {
  float best_dist = -FLT_MAX;
  uint32_t best_index;

  for (uint32_t i = 0; i < A->getVertexCount(); i++) {
    vec2d a_norm = A->getNormals()[i];

    mat2d b_rotation_T = B->rotation->transpose();
    a_norm = b_rotation_T * A->rotation->mul(a_norm);

    float best_proj = -FLT_MAX;
    vec2d best_vert;

    // Find best projection of B verticies onto normal
    for (uint32_t i = 0; i < B->getVertexCount(); i++) {
      vec2d b_vert = B->getVertexList()[i];
      float proj = dp(b_vert, -a_norm);

      if (proj > best_proj) {
        best_vert = b_vert;
        best_proj = proj;
      }
    }

    // std::cout << best_vert.x << " " << best_vert.y << std::endl;

    vec2d a_vert = A->getVertexList()[i];

    a_vert = b_rotation_T * (A->rotation->mul(a_vert) + pos_A - pos_B);

    float dist = dp(a_norm, best_vert - a_vert);

    if (dist > best_dist) {
      best_dist = dist;
      best_index = i;
    }
  }

  face_index = best_index;
  return best_dist;
}

void findIncidentFace(std::array<vec2d, 2> &v, Poly *ref, Poly *inc,
                      vec2d inc_pos, uint32_t ref_face) {

  vec2d ref_norm = ref->getNormals()[ref_face];
  // Move ref_norm to incident frame of rerence (does not have positions
  // factored in)
  ref_norm = ref->rotation->mul(ref_norm);
  ref_norm = inc->rotation->transpose() * ref_norm;

  // Find least normal (lowest dot product)
  uint32_t inc_face = 0;
  float min_dot = FLT_MAX;
  for (uint32_t i = 0; i < inc->getVertexCount(); i++) {
    float dot = dp(ref_norm, inc->getNormals()[i]);
    if (dot < min_dot) {
      min_dot = dot;
      inc_face = i;
    }
  }

  // Compute incident face in world coordinates
  vec2d inc_vert = inc->getVertexList()[inc_face];
  v[0] = inc->rotation->mul(inc_vert) + inc_pos;
  inc_face = inc_face + 1 >= inc->getVertexCount() ? 0 : inc_face + 1;
  inc_vert = inc->getVertexList()[inc_face];
  v[1] = inc->rotation->mul(inc_vert) + inc_pos;
}

uint32_t clipEdges(vec2d norm, float dist, std::array<vec2d, 2> &v) {
  uint32_t sp = 0;

  std::array<vec2d, 2> out = {vec2d(v[0]), vec2d(v[1])};

  float d1 = dp(norm, v[0]) - dist;
  float d2 = dp(norm, v[1]) - dist;

  if (d1 <= 0.0f)
    out[sp++] = v[0];

  if (d2 <= 0.0f)
    out[sp++] = v[1];

  if (d1 * d2 < 0.0) {
    float alpha = d1 / (d1 - d2);
    out[sp] = v[0] + (v[1] - v[0]) * alpha;
    ++sp;
  }

  v[0] = out[0];
  v[1] = out[1];

  assert(sp != 3);

  return sp;
}
