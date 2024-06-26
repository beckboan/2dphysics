#define _USE_MATH_DEFINES

#include "circle.h"
#include "AABB.h"
#include <cmath>
#include <iostream>


// Circle
Circle::Circle(float radius) : radius(radius) {
    // std::cout << "Circle" << std::endl;
}

Shape::ShapeType Circle::getType() const { return ShapeType::Circle; }

std::string Circle::getName() const { return "Circle"; }

void Circle::calculateMassProperties(float density) {
    std::shared_ptr<RigidBody> body_ref = body.lock();
    body_ref->area = float(radius * radius * M_PI);
    body_ref->m = body_ref->area * density;
    body_ref->I = body_ref->m * radius * radius / 2;
    body_ref->inv_m = (body_ref->m > 0) ? 1.0 / body_ref->m : 0;
    body_ref->inv_I = (body_ref->I > 0) ? 1.0 / body_ref->I : 0;
}

// Inertia return mass * radius * radius /2;

void Circle::createAABB() {
    std::shared_ptr<RigidBody> body_temp = body.lock();
    float position_x = body_temp->position.x;
    float position_y = body_temp->position.y;
    aabb.setMax(position_x + radius, position_y + radius);
    aabb.setMin(position_x - radius, position_y - radius);
    // std::cout << aabb->max.x << aabb->max.y << std::endl;
}
