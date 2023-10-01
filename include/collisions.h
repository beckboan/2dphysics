#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "rigidbody.h"
#include <memory>
#include <iostream>

struct Manifold
{
    Manifold(std::shared_ptr<RigidBody> A_, std::shared_ptr<RigidBody> B_);

    std::shared_ptr<RigidBody> A;
    std::shared_ptr<RigidBody> B;

    void collisionCaller(std::shared_ptr<RigidBody> body1, std::shared_ptr<RigidBody> body2);
};


bool CirclevsCircle(std::shared_ptr<RigidBody> A, std::shared_ptr<RigidBody> B);
bool CirclevsRect(std::shared_ptr<RigidBody> A, std::shared_ptr<RigidBody> B);
bool RectvsRect(std::shared_ptr<RigidBody> A, std::shared_ptr<RigidBody> B);

#endif