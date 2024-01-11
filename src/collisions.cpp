#include "collisions.h"
#include "circle.h"
#include "common.h"
#include "edge.h"
#include "mathfuncs.h"
#include "shape.h"
#include <cassert>
#include <cfloat>
#include <cmath>
#include <iostream>
#include <utility>

Manifold::Manifold(std::shared_ptr<RigidBody> A_, std::shared_ptr<RigidBody> B_) : A(std::move(A_)), B(std::move(B_)) {
    // std::cout << "Manifold Created" << std::endl;
    e = std::min(A->restitution, B->restitution);
    df = std::sqrt(A->dynamic_friction * B->dynamic_friction);
    sf = std::sqrt(A->static_friction * B->dynamic_friction);
    penetration = 0.0;
    contact_count = 0;
}

void Manifold::solve() {
    for (uint32_t i = 0; i < contact_count; i++) {
        // Calculate vector from COM to contact
        vec2d a_con = contacts[i] - A->position;
        vec2d b_con = contacts[i] - B->position;

        // Compute relative velocity
        vec2d r_vel = B->velocity + cp(B->angular_velocity, b_con) - A->velocity - cp(A->angular_velocity, a_con);

        // Compute relative velocity along normal
        float contact_vel = dp(r_vel, normal);
        // std::cout << contact_vel << std::endl;

        // Only solve if objects are moving towards each other
        if (contact_vel > 0.0)
            return;

        // Method from Chris Hecker's 3D Dynamics in Game Developer Maganize 1997
        float acn = cp(a_con, normal);
        float bcn = cp(b_con, normal);

        float inv_mass_sum = A->inv_m + B->inv_m + (acn * acn) * A->inv_I + (bcn * bcn) * B->inv_I;
        float j = float((-(e + 1.0) * contact_vel)) / inv_mass_sum;
        j /= (float)contact_count;

        vec2d imp = normal * j;
        vec2d imp_neg = -imp;

        // if (std::abs(imp.length() - 0.0) < EPSILON)
        //   return;

        B->applyLinearImpulse(imp, b_con);
        A->applyLinearImpulse(imp_neg, a_con);

        r_vel = B->velocity + cp(B->angular_velocity, b_con) - A->velocity - cp(A->angular_velocity, a_con);

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
    } else if (A_type == Shape::ShapeType::Poly && B_type == Shape::ShapeType::Circle) {
        reverse = true;
        CirclevsPoly();
    } else if (A_type == Shape::ShapeType::Circle && B_type == Shape::ShapeType::Poly) {
        CirclevsPoly();
    } else if (A_type == Shape::ShapeType::Circle && B_type == Shape::ShapeType::Circle) {
        CirclevsCircle();
    } else if (A_type == Shape::ShapeType::Edge && B_type == Shape::ShapeType::Edge) {
        // Edge vs Edge not supported
        return;
    } else if (A_type == Shape::ShapeType::Poly && B_type == Shape::ShapeType::Edge) {
        PolyvsEdge();
    } else if (A_type == Shape::ShapeType::Edge && B_type == Shape::ShapeType::Poly) {
        reverse = true;
        PolyvsEdge();
    } else if (A_type == Shape::ShapeType::Circle && B_type == Shape::ShapeType::Edge) {
        CirclevsEdge();
    } else if (A_type == Shape::ShapeType::Edge && B_type == Shape::ShapeType::Circle) {
        reverse = true;
        CirclevsEdge();
    }
}

void Manifold::CirclevsCircle() {
    //    std::cout << "Circle Collision" << std::endl;
    auto *C1 = dynamic_cast<Circle *>(A->shape.get());
    auto *C2 = dynamic_cast<Circle *>(B->shape.get());

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
    //    std::cout << "Circle/Polygon Collision" << std::endl;

    RigidBody *circ_bod;
    RigidBody *poly_bod;
    Circle *C;
    Poly *P;

    if (reverse) {
        C = dynamic_cast<Circle *>(B->shape.get());
        circ_bod = B.get();
        P = dynamic_cast<Poly *>(A->shape.get());
        poly_bod = A.get();
    } else {
        C = dynamic_cast<Circle *>(A->shape.get());
        circ_bod = A.get();
        P = dynamic_cast<Poly *>(B->shape.get());
        poly_bod = B.get();
    }

    float total_radius = C->radius + P->poly_radius;

    contact_count = 0;

    vec2d center = circ_bod->position;

    center = P->rotation->transpose() * (center - poly_bod->position);

    uint32_t normal_index;

    float sep = findCirclePolyMinPenetration(normal_index, C, P, center);
    if (sep > total_radius)
        return;

    penetration = total_radius - sep;

    vec2d s = P->getVertexList()[normal_index];
    // Need to safe normal index, so don't increment
    uint32_t next_normal_index = normal_index + 1 < P->getVertexCount() ? normal_index + 1 : 0;
    vec2d end = P->getVertexList()[next_normal_index];

    vec2d v1 = end - s;
    vec2d v2 = s - end;

    float dp1 = dp(v1, center - s);
    float dp2 = dp(v2, center - end);

    if (dp1 <= 0.0) {
        if (distSquared(center, s) > total_radius * total_radius)
            return;

        contact_count = 1;
        vec2d norm = s - center;
        norm = (P->rotation->mul(norm)).normalize();
        normal = norm;
        contacts[0] = P->rotation->mul(s) + poly_bod->position;
    } else if (dp2 <= 0.0) {
        if (distSquared(center, end) > total_radius * total_radius)
            return;

        contact_count = 1;
        vec2d norm = end - center;
        norm = (P->rotation->mul(norm)).normalize();
        normal = norm;
        contacts[0] = P->rotation->mul(end) + poly_bod->position;
    } else {
        vec2d norm = P->getNormals()[normal_index];

        // Check if actually within distance of poylgon face
        if (dp(norm, center - s) > total_radius)
            return;

        contact_count = 1;
        norm = (P->rotation->mul(norm));
        contacts[0] = -norm * C->radius + circ_bod->position;
        normal = -norm;
    }
}

struct AxisData {
    enum Type { primary_edge, primary_poly };
    vec2d normal;
    Type type{};
    uint32_t primary_normal_index = 0;
    float separation = 0.0;
};

float findMTVEdgePoly(uint32_t &index, const vec2d &start_line, const vec2d &end_line, Poly *P, const vec2d &pos_polygon) {
    float best_dist = -FLT_MAX;
    uint32_t best_index;

    // Calculate the normal vectors of the line (start_line to end_line)
    vec2d line_dir = end_line - start_line;
    vec2d line_normal1 = (vec2d(line_dir.y, -line_dir.x)).normalize();
    // std::cout << line_normal1.x << " " << line_normal1.y << std::endl;
    vec2d line_normal2 = -line_normal1; // Invert the normal for the second side

    mat2d polygon_rotation_T = P->rotation->transpose();

    for (uint32_t j = 0; j < 2; ++j) {
        vec2d line_normal = (j == 0) ? line_normal1 : line_normal2;
        line_normal = polygon_rotation_T * line_normal;

        float best_proj = -FLT_MAX;
        vec2d best_vert;
        for (uint32_t i = 0; i < P->getVertexCount(); i++) {
            vec2d b_vert = P->getVertexList()[i];
            float proj = dp(b_vert, -line_normal);

            if (proj > best_proj) {
                best_vert = b_vert;
                best_proj = proj;
            }
        }

        vec2d a_vert = (j == 0) ? start_line : end_line;
        a_vert = polygon_rotation_T * (a_vert - pos_polygon);

        float dist = dp(line_normal, best_vert - a_vert);
        if (dist > best_dist) {
            best_dist = dist;
            best_index = j;
        }
    }

    index = best_index;
    return best_dist;
}

float findMTVPolyEdge(uint32_t &index, const vec2d &start_line, const vec2d &end_line, Poly *P, const vec2d &pos_polygon) {
    float best_dist = -FLT_MAX;
    uint32_t best_index;

    for (uint32_t i = 0; i < P->getVertexCount(); i++) {
        vec2d a_norm = P->getNormals()[i];
        a_norm = P->rotation->mul(a_norm);

        float best_proj = -FLT_MAX;
        vec2d best_vert;

        for (uint32_t j = 0; j < 2; j++) {
            vec2d b_vert = (j == 0) ? start_line : end_line;
            float proj = dp(b_vert, -a_norm);

            if (proj > best_proj) {
                best_vert = b_vert;
                best_proj = proj;
            }
        }

        vec2d a_vert = P->getVertexList()[i];
        a_vert = P->rotation->mul(a_vert) + pos_polygon;

        float dist = dp(a_norm, best_vert - a_vert);
        if (dist > best_dist) {
            best_dist = dist;
            best_index = i;
        }
    }

    index = best_index;
    return best_dist;
}
// void findEdgePolyIncident(std::array<vec2d, 2> &v, Poly *P, const vec2d &poly_pos, const vec2d &s, const vec2d &e, uint32_t index) {
//     vec2d line_dir = e - s;
//     vec2d line_norm = vec2d(line_dir.x, -line_dir.y).normalize();
//
//     vec2d normal = (index == 0) ? line_norm : -line_norm;
//
//     normal = P->rotation->transpose() * normal;
//
//     uint32_t inc_face = 0;
//     float min_dot = FLT_MAX;
//     for (uint i = 0; i < P->getVertexCount(); i++) {
//         float dot = dp(normal, P->getNormals()[i]);
//         if (dot < min_dot) {
//             min_dot = dot;
//             inc_face = i;
//         }
//     }
//
//     vec2d inc_vert = P->getVertexList()[inc_face];
//     v[0] = P->rotation->mul(inc_vert) + poly_pos;
//     inc_face = inc_face + 1 >= P->getVertexCount() ? 0 : inc_face + 1;
//     inc_vert = P->getVertexList()[inc_face];
//     v[1] = P->rotation->mul(inc_vert) + poly_pos;
// }

void Manifold::PolyvsEdge() {
    Poly *P;
    Edge *E;
    vec2d poly_pos;

    //    std::cout << "Poly/Edge Collision" << std::endl;
    if (reverse) {
        P = dynamic_cast<Poly *>(B->shape.get());
        poly_pos = B->position;
        E = dynamic_cast<Edge *>(A->shape.get());
    } else {
        P = dynamic_cast<Poly *>(A->shape.get());
        poly_pos = A->position;
        E = dynamic_cast<Edge *>(B->shape.get());
    }
    contact_count = 0;

    vec2d s = E->start_vertex;
    vec2d end = E->end_vertex;

    float total_radius = P->poly_radius + E->edge_radius;

    uint32_t poly_norm_index;
    float pen_A = findMTVPolyEdge(poly_norm_index, s, end, P, poly_pos);
    if (pen_A > total_radius) {
        return;
    }

    uint32_t edge_norm_index;
    float pen_B = findMTVEdgePoly(edge_norm_index, s, end, P, poly_pos);
    if (pen_B > total_radius) {
        return;
    }

    AxisData PrimaryAxis;

    const float k_tol = 0.1 * linearSlop;
    if (pen_A > pen_B + k_tol) {
        PrimaryAxis.type = AxisData::primary_poly;
        PrimaryAxis.normal = P->getNormals()[poly_norm_index];
        PrimaryAxis.separation = pen_B;
        PrimaryAxis.primary_normal_index = poly_norm_index;
    } else {
        PrimaryAxis.type = AxisData::primary_edge;
        vec2d line_dir = end - s;
        vec2d line_normal = (vec2d(line_dir.y, -line_dir.x)).normalize();
        PrimaryAxis.normal = (edge_norm_index) == 0 ? line_normal : -line_normal;
        PrimaryAxis.separation = pen_A;
        PrimaryAxis.primary_normal_index = edge_norm_index;
    }

    std::array<vec2d, 2> incident_edge;
    vec2d r_v1;
    vec2d r_v2;
    bool flip;

    if (PrimaryAxis.type == AxisData::primary_edge) {
        uint32_t best_index = 0;
        float best_value = FLT_MAX;
        for (uint32_t i = 0; i < P->getVertexCount(); i++) {
            vec2d poly_norm = P->getNormals()[i];
            poly_norm = P->rotation->mul(poly_norm);
            float value = dp(PrimaryAxis.normal, poly_norm);
            if (value < best_value) {
                best_value = value;
                best_index = i;
            }
        }

        incident_edge[0] = P->getVertexList()[best_index];
        incident_edge[0] = P->rotation->mul(incident_edge[0]) + poly_pos;
        uint32_t best_index2 = best_index + 1 >= P->getVertexCount() ? 0 : best_index + 1;
        incident_edge[1] = P->getVertexList()[best_index2];
        incident_edge[1] = P->rotation->mul(incident_edge[1]) + poly_pos;

        r_v1 = (edge_norm_index == 1) ? end : s; //(edge_norm_index == 1);
        r_v2 = (edge_norm_index == 1) ? s : end; //(edge_norm_index == 1);
        normal = PrimaryAxis.normal;
        // std::cout << normal.x << " " << normal.y << std::endl;

        flip = true;
    }

    else {
        incident_edge[0] = end;
        incident_edge[1] = s;

        r_v1 = P->getVertexList()[PrimaryAxis.primary_normal_index];
        uint32_t primary_normal_index2 = PrimaryAxis.primary_normal_index + 1 >= P->getVertexCount() ? 0 : PrimaryAxis.primary_normal_index + 1;
        r_v2 = P->getVertexList()[primary_normal_index2];

        r_v1 = P->rotation->mul(r_v1) + poly_pos;
        r_v2 = P->rotation->mul(r_v2) + poly_pos;

        normal = P->getNormals()[PrimaryAxis.primary_normal_index];
        flip = false;
    }

    vec2d side_tangent = (r_v2 - r_v1).normalize();

    // Find orthogonal
    vec2d side_normal(side_tangent.y, -side_tangent.x);

    // Finding front offsets and sides
    float front_offset = dp(side_normal, r_v1);
    float neg_side = -dp(side_tangent, r_v1) + total_radius;
    float pos_side = dp(side_tangent, r_v2) + total_radius;

    if (clipEdges(-side_tangent, neg_side, incident_edge) < 2) {
        DBG("Clipp Error");
        return;
    }

    if (clipEdges(side_tangent, pos_side, incident_edge) < 2) {
        DBG("Clipp Error");
        return;
    }
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
    contact_count = clipped_points;
    normal = flip ? -side_normal : side_normal;
}

void Manifold::CirclevsEdge() {
    //    std::cout << "Circle/Edge Collision" << std::endl;

    RigidBody *circ_bod;
    RigidBody *edge_bod;
    Circle *C;
    Edge *E;

    if (reverse) {
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
    vec2d s = E->start_vertex;
    vec2d end = E->end_vertex;
    vec2d v1 = end - s;
    vec2d v2 = s - end;

    float total_radius = C->radius + E->edge_radius;

    // Start with typical CCW norm (doesn't matter for edge)

    vec2d norm = vec2d(v1.y, -v1.x);
    norm = norm.normalize();

    // Want to determine which side of the edge the circle is on
    // Also check if circle is closer to vertex or face
    //   |      A       |
    //   <-------------->
    //   |      B       |

    float dp1 = dp(v1, center - s);
    float dp2 = dp(v2, center - end);

    if (dp1 <= 0.0) {
        if (distSquared(center, s) > total_radius * total_radius)
            return;
        contact_count = 1;
        contacts[0] = s;
        norm = s - center;
        normal = norm.normalize();
        penetration = C->radius - dist(center, s);
    } else if (dp2 <= 0.0) {
        if (distSquared(center, end) > total_radius * total_radius)
            return;
        contact_count = 1;
        contacts[0] = end;
        norm = end - center;
        normal = norm.normalize();
        penetration = C->radius - dist(center, s);
    } else {
        float edge_sep = dp(center - edge_bod->position, norm);
        float edge_abs = std::abs(edge_sep);
        // On normal side
        if (edge_abs < total_radius && edge_sep < 0) {
            normal = norm;
            contact_count = 1;
            penetration = C->radius - edge_abs + E->edge_radius;
            contacts[0] = normal * C->radius + center;
        }
        // On opposite side
        else if (edge_abs < total_radius && edge_sep > 0) {
            normal = -norm;
            contact_count = 1;
            penetration = C->radius - edge_abs + E->edge_radius;
            contacts[0] = normal * total_radius + center;
        }
        // Not contacting
        else
            return;
    }
}

void Manifold::PolyvsPoly() {
    //    std::cout << "Poly Collision" << std::endl;
    Poly *P1 = dynamic_cast<Poly *>(A->shape.get());
    Poly *P2 = dynamic_cast<Poly *>(B->shape.get());

    contact_count = 0;
    float total_radius = P1->poly_radius + P2->poly_radius;
    // std::cout << total_radius << std::endl;

    uint32_t face_A = 0;
    float pen_A = findAOLP(face_A, P1, P2, A->position, B->position);
    //    DBG(A->position.y);
    //    DBG(face_A);
    if (pen_A > total_radius) {
        // std::cout << "No Collision" << std::endl;
        return;
    }
    uint32_t face_B = 0;
    float pen_B = findAOLP(face_B, P2, P1, B->position, A->position);
    //    DBG(face_B);
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
float findAOLP(uint32_t &face_index, Poly *A, Poly *B, const vec2d &pos_A, const vec2d &pos_B) {
    float best_dist = -FLT_MAX;
    uint32_t best_index;

    for (uint32_t i = 0; i < A->getVertexCount(); i++) {
        vec2d a_norm = A->getNormals()[i];

        mat2d b_rotation_T = B->rotation->transpose();
        a_norm = b_rotation_T * A->rotation->mul(a_norm);

        float best_proj = -FLT_MAX;
        vec2d best_vert;

        // Find best projection of B verticies onto normal
        for (uint32_t j = 0; j < B->getVertexCount(); j++) {
            vec2d b_vert = B->getVertexList()[j];
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

void findIncidentFace(std::array<vec2d, 2> &v, Poly *ref, Poly *inc, const vec2d &inc_pos, uint32_t ref_face) {
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

float findCirclePolyMinPenetration(uint32_t &normal_index, Circle *C, Poly *P, const vec2d &c) {
    float best_dist = -FLT_MAX;
    uint32_t best_index = 0;
    for (uint32_t i = 0; i < P->getVertexCount(); i++) {
        auto temp_norm = P->getNormals()[i];
        auto temp_vert = P->getVertexList()[i];

        float sep = dp(temp_norm, c - temp_vert);
        if (sep > best_dist) {
            best_dist = sep;
            best_index = i;
        }
    }

    normal_index = best_index;
    return best_dist;
}

void Manifold::correctPositions() {
    const float k_slop = 0.05;
    const float percent = 0.4;
    vec2d correction = normal * (std::max(penetration - k_slop, 0.0f) / (A->inv_m + B->inv_m)) * percent;
    A->position -= correction * A->inv_m;
    B->position += correction * B->inv_m;
}
