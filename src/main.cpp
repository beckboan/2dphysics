#include <iostream>
#include "simplephysics.h"
//#include "tests.h"

#define DBG(msg) std::cout << msg <<std::endl;

int main(int, char**)
{
    World world;
    Scene scene(1200,800);

    vec2d position = vec2d(500, 500);
    float density = 1000;
    vec2d movetopos = vec2d(500,500);

    // std::unique_ptr<Shape> shp1 = std::make_unique<Circle>(1);
    // std::shared_ptr<RigidBody> bod1 = std::make_shared<RigidBody>(shp1,position,1000);
    // bod1->shape->setBody(bod1);

    std::vector<vec2d> verticies = {vec2d(0,0), vec2d(5,0), vec2d(5,5), vec2d(0,5), vec2d(7.5,10)};

    std::unique_ptr<Shape> pol = std::make_unique<Poly>(verticies);
    std::unique_ptr<Shape> cir = std::make_unique<Circle>(100.0);
    std::shared_ptr<RigidBody> bod = std::make_shared<RigidBody>(cir, position, density);
    // std::cout << bod->position.x << "  " << bod->position.y << std::endl;
    bod->shape->setBody(bod);
    //bod->moveto(movetopos);

    scene.drawBody(bod);
    scene.drawAABB(bod);

    std::cin.get();

}
