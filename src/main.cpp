#include <iostream>
#include "simplephysics.h"
//#include "tests.h"

#define DBG(msg) std::cout << msg <<std::endl;

int main(int, char**){
    PhysicsWorld world;

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


    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow("OpenGL Test",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 800, SDL_WINDOW_OPENGL);
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear (renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    bod->shape->draw(renderer, position);
    SDL_RenderPresent(renderer);

    std::cin.get();

}
