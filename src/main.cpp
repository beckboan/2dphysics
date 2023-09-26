#include <iostream>
#include "simplephysics.h"
//#include "tests.h"

#define DBG(msg) std::cout << msg <<std::endl;

int main(int, char**){
    World world;
    Scene scene;

    vec2d position = vec2d(400, 400);
    float density = 1000;
    vec2d movetopos = vec2d(0,0);

    // std::unique_ptr<Shape> shp1 = std::make_unique<Circle>(1);
    // std::shared_ptr<RigidBody> bod1 = std::make_shared<RigidBody>(shp1,position,1000);
    // bod1->shape->setBody(bod1);

    std::vector<vec2d> verticies = {vec2d(0,0), vec2d(300,100), vec2d(200,0), vec2d(100,0), vec2d(100,100), vec2d(200,100), vec2d(200,110), vec2d(200,-200), vec2d(800,-0)};

    std::unique_ptr<Shape> pol = std::make_unique<Poly>(verticies);
    std::shared_ptr<RigidBody> bod = std::make_shared<RigidBody>(pol, position, density);
    bod->shape->setBody(bod);
    //bod->moveto(movetopos);

    scene.drawBody(bod);

    std::cin.get();

}
