#include <iostream>
#include "mathfuncs.h"
#include "physicsobject.h"
#include "physicsworld.h"


int main(int, char**){

    PhysicsObject::CreateCircleBody(10, vec2d(0.0f, 0.0f), 500, .1, 0);
    PhysicsObject::CreateBoxBody(10, 10, vec2d(0.0f, 0.0f), 500, 0.3, 0);
    //std::cout << vector1.x << ", " << vector1.y << std::endl;
}
