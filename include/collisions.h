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

    void collisionCaller();
};


bool CirclevsCircle(std::shared_ptr<RigidBody> A, std::shared_ptr<RigidBody> B);
bool CirclevsPoly(std::shared_ptr<RigidBody> A, std::shared_ptr<RigidBody> B);
bool PolyvsPoly(std::shared_ptr<RigidBody> A, std::shared_ptr<RigidBody> B);

#endif