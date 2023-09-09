#include "physicsobject.h"
#include "physicsworld.h"
#include <cmath>
#include <iostream>


PhysicsObject::PhysicsObject(vec2d position, vec2d linear_velocity, float rotation, float rotational_velocity,
    const float mass, const float restitution, const float area, const bool is_static,
    ShapeType shape_type): position(position), linear_velocity(vec2d(0,0)), rotation(0), rotational_velocity(0),
    mass(mass), restitution(restitution), area(area), is_static(is_static), shape_type(shape_type)
    {};


bool PhysicsObject::CreateCircleBody(float radius, float mass, float restitution, bool is_static) {
    float area =  radius * radius * M_PI;

    if(area < WorldParams::min_body_area || area > WorldParams::max_body_area) {
        std::cout << "Circle radius outside of world parameters" << std::endl;
        return false;

    }

    if(mass < WorldParams::min_body_mass || area > WorldParams::max_body_mass) {
        std::cout << "Circle mass outside of world parameters" << std::endl;
        return false;

    }

    clamp(restitution, 0.0f, 1.0f);

    std::cout << "Circle created" << std::endl;
    std::cout << restitution << std::endl;
    return true;
}

