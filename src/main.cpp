#include <iostream>
#include "mathfuncs.h"
#include "shape.h"
#include <typeinfo>
#include "rigidbody.h"
#include "physicsworld.h"

int main(int, char**){
    PhysicsWorld world;

    world.addCircle(5.0, vec2d(0, 0), 1000);
    world.addRect(10,30, vec2d(0,0), 2000);
}
