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
    void solve();
    void applyCollisionImpulse();

    const uint32_t& getContactCount() const {return contact_count;}

    void CirclevsCircle();
    void CirclevsPoly();
    void PolyvsCircle();
    void PolyvsPoly();

    private:
    float penetration;
    uint32_t contact_count = 0;
    vec2d normal = vec2d(0,0);
    vec2d contacts[2] = {vec2d(0,0), vec2d(0,0)};
    float e;
    float df;
    float sf;
};




#endif