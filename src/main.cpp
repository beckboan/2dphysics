#include <iostream>
#include "simplephysics.h"
//#include "tests.h"

#define DBG(msg) std::cout << msg <<std::endl;

int main(int, char**)
{
    World world;

    vec2d position = vec2d(0, 0);
    float density = 1000;
    vec2d movetopos = vec2d(-70,100);

    // std::unique_ptr<Shape> shp1 = std::make_unique<Circle>(1);
    // std::shared_ptr<RigidBody> bod1 = std::make_shared<RigidBody>(shp1,position,1000);
    // bod1->shape->setBody(bod1);

    std::vector<vec2d> verticies = {vec2d(0,0), vec2d(5,0), vec2d(5,5), vec2d(0,5), vec2d(7.5,10)};

    world.addCircle(10, position, 1000);
    world.addPoly(verticies, position, 1000);
    world.addCircle(8, position, 1200);

    world.checkCollisions();

    std::cin.get();

}
