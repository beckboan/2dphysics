#include <iostream>
#include "simplephysics.h"

#define GL_GLEXT_PROTOTYPES
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"

#define DBG(msg) std::cout << msg <<std::endl;

int main(int, char**){
    PhysicsWorld world;

    vec2d position = vec2d(0,0);
    // world.addCircle(1, position, 1000);
    // world.addRect(1, 1, position, 1000);


    std::unique_ptr<Shape> shp = std::make_unique<Circle>(1);
    std::shared_ptr<RigidBody> bod = std::make_shared<RigidBody>(shp,position,1000);

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow("OpenGL Test",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, SDL_WINDOW_OPENGL);
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    shp->draw(renderer, position);

    std::cin.get();
}
