#include "circle.h"
#include "iostream"
#include <memory>

//Circle
Circle::Circle(float radius): radius(radius) 
{
    // std::cout << "Circle" << std::endl;
}

Shape::ShapeType Circle::getType() const {return ShapeType::Circle;}

std::string Circle::getName() const {return "Circle";}

void Circle::calculateMassProperties(float& density) 
{
    std::shared_ptr<RigidBody> body_ref = body.lock();
    body_ref->area = radius * radius * M_PI;
    body_ref->m = body_ref->area *density;
    body_ref->I = body_ref->m * radius * radius /2;
    body_ref->inv_m = (body_ref->m) ? 1.0f / body_ref -> I : 0;
    body_ref->inv_I = (body_ref->I) ? 1.0f / body_ref -> I : 0;
}

//Inertia return mass * radius * radius /2;

void Circle::createAABB() 
{
    std::shared_ptr<RigidBody> body_temp = body.lock();
    float position_x = body_temp->position.x;
    float position_y = body_temp->position.y;
    aabb = std::make_unique<AABB>();
    aabb->max.assign(radius,radius);
    aabb->min.assign(-radius,-radius);
}
