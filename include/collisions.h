#include "rigidbody.h"
#include <memory>
#include <iostream>

#ifndef COLLISIONS_H
#define COLLISIONS_H

void collisionCaller(std::shared_ptr<RigidBody> body1, std::shared_ptr<RigidBody> body2) {}

bool checkCircleCollision(std::shared_ptr<RigidBody> body1, std::shared_ptr<RigidBody> body2) {
    return true;
}

#endif