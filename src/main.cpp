#include <iostream>
#include "mathfuncs.h"
#include "shape.h"
#include <typeinfo>
#include "rigidbody.h"
#include "physicsworld.h"

#define DBG(msg) std::cout << msg <<std::endl;

int main(int, char**){
    PhysicsWorld world;

    world.addCircle(1, vec2d(0, 0), 1000);
    world.addRect(1, 1, vec2d(0, 0), 1000);

    //world.printPhysicsObjects();
    //world.printAreas();

    std::cin.get();
}
