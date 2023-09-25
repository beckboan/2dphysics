#include <iostream>
#include "physicsworld.h"
#include "mathfuncs.h"
#include "shape.h"

#define DBG(msg) std::cout << msg <<std::endl;

//Creating and Destroying Rigid Bodies

bool PhysicsWorld::addCircle (float radius, vec2d position, float density) {

    float area =  radius * radius * M_PI;
    if (!isValidArea(area)) return false;
    if (!isValidDensity(density)) return false;

    std::unique_ptr<Shape> shp = std::make_unique<Circle>(radius);
    std::shared_ptr<RigidBody> bod = std::make_shared<RigidBody>(shp,position,density);
    bod->shape->setBody(bod);
    bod->rigidIni();

    world_objects.emplace_back(bod);
    std::cout << "Circle Added" << std::endl;
    return true;
};

bool PhysicsWorld::addRect(float width, float height, vec2d position, float density) {

    float area =  width * height;

    if (!isValidArea(area)) return false;
    if (!isValidDensity(density)) return false;

    std::unique_ptr<Shape> shp = std::make_unique<Poly>(width, height);
    std::shared_ptr<RigidBody> bod = std::make_shared<RigidBody>(shp,position,density);
    bod->shape->setBody(bod);
    bod->rigidIni();

    world_objects.emplace_back(bod);
    std::cout << "Rectangle Added" << std::endl;
    return true;

}
void PhysicsWorld::removePhysicsObject (std::shared_ptr<RigidBody>) {

};

// Physics Validation

bool PhysicsWorld::isValidArea(float& area) {
    if(area < WorldParams::min_body_area || area > WorldParams::max_body_area) {
        std::cout << "Area outside of world parameters" << std::endl;
        return false;
    }
    return true;
}

bool PhysicsWorld::isValidDensity(float& density) {
    if(density < WorldParams::min_body_density || density > WorldParams::max_body_density) {
        std::cout << "Density outside of world parameters" << std::endl;
        return false;
    }
    return true;
}

//

