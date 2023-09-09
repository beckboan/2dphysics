#include <iostream>
#include "mathfuncs.h"
#include "shape.h"
#include <typeinfo>
#include "rigidbody.h"
#include "physicsworld.h"

int main(int, char**){
    PhysicsWorld world;
    Circle c(5.0f);
    RigidBody *b = new RigidBody(&c, vec2d(0.0,0.0));

    world.addPhysicsObject(b);
}
