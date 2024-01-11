#include "edge.h"
#include <string>
#include <utility>

Edge::Edge(vec2d s, vec2d e) : start_vertex(std::move(s)), end_vertex(std::move(e)) { centroid = (start_vertex + end_vertex) / 2; }

void Edge::createAABB() {
    vec2d v1 = rotation->mul(start_vertex);
    vec2d v2 = rotation->mul(end_vertex);

    float max_x = std::max(v1.x, v2.x);
    float max_y = std::max(v1.y, v2.y);
    float min_x = std::min(v1.x, v2.x);
    float min_y = std::min(v1.y, v2.y);

    std::shared_ptr<RigidBody> body_temp = body.lock();
    aabb.setMax(max_x, max_y);
    aabb.setMin(min_x, min_y);
    // std::cout << min_x << min_y << std::endl;

    // std::cout << aabb.getMin().x << aabb.getMin().y << aabb.getMax().x
    //           << aabb.getMax().y << std::endl;
}

// void Edge::createAABB() {
//   std::shared_ptr<RigidBody> body_temp = body.lock();
//   float position_x = body_temp->position.x;
//   float position_y = body_temp->position.y;
//   aabb.setMax(position_x, position_y);
//   aabb.setMin(position_x, position_y);
//   // std::cout << aabb->max.x << aabb->max.y << std::endl;
// }
Shape::ShapeType Edge::getType() const { return ShapeType::Edge; }

std::string Edge::getName() const { return "Edge"; }

void Edge::calculateMassProperties(float density) {
    std::shared_ptr<RigidBody> body_ref = body.lock();
    body_ref->area = 0;
    body_ref->m = body_ref->area * density;
    body_ref->I = 0;
    body_ref->inv_m = (body_ref->m > 0.0) ? 1.0f / body_ref->I : 0;
    body_ref->inv_I = (body_ref->I > 0.0) ? 1.0f / body_ref->I : 0;
}
