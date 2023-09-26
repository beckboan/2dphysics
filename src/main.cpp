#include <iostream>
#include "simplephysics.h"
//#include "tests.h"

#define DBG(msg) std::cout << msg <<std::endl;

int main(int, char**)
{
    World world;
    Scene scene(1200,800);

    vec2d position = vec2d(0, 0);
    float density = 1000;
    vec2d movetopos = vec2d(0,0);

    // std::unique_ptr<Shape> shp1 = std::make_unique<Circle>(1);
    // std::shared_ptr<RigidBody> bod1 = std::make_shared<RigidBody>(shp1,position,1000);
    // bod1->shape->setBody(bod1);

    std::vector<vec2d> verticies = {vec2d(0,0), vec2d(100,0), vec2d(100,100), vec2d(0,100), vec2d(150,200)};

    std::unique_ptr<Shape> pol = std::make_unique<Poly>(verticies);
    std::unique_ptr<Shape> cir = std::make_unique<Circle>(100.0);
    std::shared_ptr<RigidBody> bod = std::make_shared<RigidBody>(pol, position, density);
    // std::cout << bod->position.x << "  " << bod->position.y << std::endl;
    bod->shape->setBody(bod);
    // bod->moveto(movetopos);

    scene.drawBody(bod);

    std::cin.get();

}
