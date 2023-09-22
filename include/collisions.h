#include "rigidbody.h"
#include "shape.h"
#include <memory>
#include <iostream>

#ifndef COLLISIONS_H
#define COLLISIONS_H

void collisionCaller(std::shared_ptr<RigidBody> body1, std::shared_ptr<RigidBody> body2) {}

bool checkCircleCollision(std::shared_ptr<RigidBody> body1, std::shared_ptr<RigidBody> body2) {
    float radius1 = body1->shape->getVar('r');
    return true;
}

#endif