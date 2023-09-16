#include <iostream>
#include "physicsworld.h"
#include "mathfuncs.h"
#include "rigidbody.h"
#include "shape.h"

#define DBG(msg) std::cout << msg <<std::endl;

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

    std::unique_ptr<Shape> shp = std::make_unique<Circle>(radius);
    std::shared_ptr<RigidBody> bod = std::make_shared<RigidBody>(shp,position,density);
    bod->rigidIni();

    world_objects.emplace_back(bod);
    std::cout << "Circle Added" << std::endl;
    return true;
};

bool PhysicsWorld::addRect(float width, float height, vec2d position, float density) {

    float area =  width * height;

    if(area < WorldParams::min_body_area || area > WorldParams::max_body_area) {
        std::cout << "Rectangle radius outside of world parameters" << std::endl;
        return false;

    }

    if(density < WorldParams::min_body_density || density > WorldParams::max_body_density) { // FIX ISSUE WITH MASS
        std::cout << "Rectangle density outside of world parameters" << std::endl;
        return false;
    }

    std::unique_ptr<Shape> shp = std::make_unique<Rect>(width, height);
    std::shared_ptr<RigidBody> bod = std::make_shared<RigidBody>(shp,position,density);
    bod->rigidIni();

    world_objects.emplace_back(bod);
    std::cout << "Rectangle Added" << std::endl;
    return true;

}
void PhysicsWorld::removePhysicsObject (std::shared_ptr<RigidBody>) {

};

//add step function here

void PhysicsWorld::printPhysicsObjects() {
    for (auto i: world_objects) {
        std::cout << i->shape->getName() << std::endl;
    }
}


// void worldStep();