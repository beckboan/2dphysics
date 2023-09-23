#include <iostream>
#include "simplephysics.h"

#define GL_GLEXT_PROTOTYPES
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"

#define DBG(msg) std::cout << msg <<std::endl;


int main(int, char**){
    PhysicsWorld world;

    vec2d position = vec2d(0 , 0);
    // world.addCircle(1, position, 1000);;

    std::unique_ptr<Shape> shp1 = std::make_unique<Circle>(100);
    std::shared_ptr<RigidBody> bod1 = std::make_shared<RigidBody>(shp1,position,1000);
    bod1->moveto(vec2d(150,150));

    std::unique_ptr<Shape> shp2 = std::make_unique<Circle>(100);
    std::shared_ptr<RigidBody> bod2 = std::make_shared<RigidBody>(shp2,position,1000);
    bod2->moveto(vec2d(250,420));



    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow("OpenGL Test",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 800, SDL_WINDOW_OPENGL);
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear (renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    bod1->shape->draw(renderer,bod1->position);
    bod1->shape->draw(renderer,bod2->position);
    SDL_RenderPresent(renderer);

    std::cout << CirclevsCircle(bod1,bod2) <<std::endl;

    std::cin.get();
}
