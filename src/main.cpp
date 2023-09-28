#include <iostream>
#include "simplephysics.h"
//#include "tests.h"

#define DBG(msg) std::cout << msg <<std::endl;

int main(int, char**)
{
    World world;
    Scene scene(1800,1000);
    scene.init();

    vec2d position = vec2d(0, 0);
    float density = 1000;
    vec2d movetopos = vec2d(600,300);

    // std::unique_ptr<Shape> shp1 = std::make_unique<Circle>(1);
    // std::shared_ptr<RigidBody> bod1 = std::make_shared<RigidBody>(shp1,position,1000);
    // bod1->shape->setBody(bod1);

    std::vector<vec2d> verticies = {vec2d(0,0), vec2d(50,0), vec2d(50,50), vec2d(0,50), vec2d(75,100)};

    std::unique_ptr<Shape> pol = std::make_unique<Poly>(verticies);
    std::unique_ptr<Shape> cir = std::make_unique<Circle>(40.0);
    std::shared_ptr<RigidBody> bod = std::make_shared<RigidBody>(pol, position, density);
    std::shared_ptr<RigidBody> bod2 = std::make_shared<RigidBody>(cir,position,density);
    // std::cout << bod->position.x << "  " << bod->position.y << std::endl;
    bod->shape->setBody(bod);
    bod2->shape->setBody(bod2);
    bod->moveto(movetopos);
    bod->shape->updateAABB();


    scene.drawBody(bod);
    scene.drawAABB(bod);
    scene.drawBody(bod2);
    scene.drawAABB(bod2);

    std::cin.get();

}
