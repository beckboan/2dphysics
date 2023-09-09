#include <iostream>
#include "physicsworld.h"
#include "mathfuncs.h"
#include "rigidbody.h"


void PhysicsWorld::addPhysicsObject (RigidBody* object) {
    world_objects.emplace_back(object);
    std::cout << "Object Added" << std::endl;
};
void PhysicsWorld::removePhysicsObject (RigidBody* object) {

};

// void worldStep();