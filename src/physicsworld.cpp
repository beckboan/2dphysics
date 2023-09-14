#include <iostream>
#include "physicsworld.h"
#include "mathfuncs.h"
#include "rigidbody.h"
#include "shape.h"


bool PhysicsWorld::addCircle (float radius, vec2d position, float density) {

    float area =  radius * radius * M_PI;

    if(area < WorldParams::min_body_area || area > WorldParams::max_body_area) {
        std::cout << "Circle radius outside of world parameters" << std::endl;
        return false;

    }

    if(density < WorldParams::min_body_density || density > WorldParams::max_body_density) { // FIX ISSUE WITH MASS
        std::cout << "Circle density outside of world parameters" << std::endl;
        return false;
    }

    std::unique_ptr<Shape> c = std::make_unique<Circle>(radius);
    RigidBody *b = new RigidBody(c, position);

    world_objects.emplace_back(b);
    std::cout << "Circle Added" << std::endl;
    return true;
};

bool PhysicsWorld::addRect(float width, float height, vec2d position, float density) {

    float area =  width * height;

    if(area < WorldParams::min_body_area || area > WorldParams::max_body_area) {
        std::cout << "Circle radius outside of world parameters" << std::endl;
        return false;

    }

    if(density < WorldParams::min_body_density || density > WorldParams::max_body_density) { // FIX ISSUE WITH MASS
        std::cout << "Circle density outside of world parameters" << std::endl;
        return false;
    }

    std::unique_ptr<Shape> c = std::make_unique<Rect>(width, height);
    RigidBody *b = new RigidBody(c, position);

    world_objects.emplace_back(b);
    std::cout << "Circle Added" << std::endl;
    return true;

}
void PhysicsWorld::removePhysicsObject (RigidBody* object) {

};

// void worldStep();