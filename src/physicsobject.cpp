#include "physicsobject.h"
#include "physicsworld.h"
#include <cmath>
#include <iostream>
#include <memory>


PhysicsObject::PhysicsObject(vec2d& position, float radius, float width, float height, const float density, const float mass,
    const float restitution, const float area, const bool is_static, ShapeType shape_type): 
    position(position), radius(radius), width(width), height(height), density(density),
    mass(mass), restitution(restitution), area(area), is_static(is_static), shape_type(shape_type)
    {
        this->linear_velocity;
        this->rotation = 0;
        this->rotational_velocity=0;
        std::cout << "Object Created" << std::endl;
    };


bool PhysicsObject::CreateCircleBody(float radius, vec2d position, float density, float restitution, bool is_static) {
    float area =  radius * radius * M_PI;

    if(area < WorldParams::min_body_area || area > WorldParams::max_body_area) {
        std::cout << "Circle radius outside of world parameters" << std::endl;
        return false;

    }

    if(density < WorldParams::min_body_density || density > WorldParams::max_body_density) { // FIX ISSUE WITH MASS
        std::cout << "Circle density outside of world parameters" << std::endl;
        return false;
    }

    float mass = density*area; 
    clamp(restitution, 0.0f, 1.0f);

    std::shared_ptr<PhysicsObject> object = std::make_shared<PhysicsObject>(position, radius, 0, 0, density, mass, restitution, area, is_static, ShapeType::Circle); //MAKE NEW OBJECT?
    return true;
}

bool PhysicsObject::CreateBoxBody(float width, float height, vec2d position, float density, float restitution, bool is_static) {
    float area =  width * height;

    if(area < WorldParams::min_body_area || area > WorldParams::max_body_area) {
        std::cout << "Circle radius outside of world parameters" << std::endl;
        return false;

    }

    if(density < WorldParams::min_body_density || density > WorldParams::max_body_density) { // FIX ISSUE WITH MASS
        std::cout << "Circle density outside of world parameters" << std::endl;
        return false;
    }

    float mass = density*area; 
    clamp(restitution, 0.0f, 1.0f);

    std::shared_ptr<PhysicsObject> object = std::make_shared<PhysicsObject>(position, 0, width, height, density, mass, restitution, area, is_static, ShapeType::Box); //MAKE NEW OBJECT?
    return true;
}