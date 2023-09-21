#include <iostream>
#include "simplephysics.h"

#define GL_GLEXT_PROTOTYPES
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"

#define DBG(msg) std::cout << msg <<std::endl;

void drawCircle(SDL_Renderer * renderer, vec2d& position, float radius) 
{ 
    float diameter = radius*2;
    float x = (radius - 1);
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - diameter;

    while (x >= y) {
        SDL_RenderDrawPoint(renderer, position.x + x, position.y - y);
        SDL_RenderDrawPoint(renderer, position.x + x, position.y + y);
        SDL_RenderDrawPoint(renderer, position.x - x, position.y - y);
        SDL_RenderDrawPoint(renderer, position.x - x, position.y + y);
        SDL_RenderDrawPoint(renderer, position.x + y, position.y - x);
        SDL_RenderDrawPoint(renderer, position.x + y, position.y + x);
        SDL_RenderDrawPoint(renderer, position.x - y, position.y - x);
        SDL_RenderDrawPoint(renderer, position.x - y, position.y + x);

        if (err <= 0) {
            ++y;
            err+= dy;
            dx +=2;
        }

        if (err > 0) {
            --x;
            dx +=2;
            err += (dx-diameter);
        }
    }
}

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
    drawCircle(renderer, position, 5);

    std::cin.get();
}
