#include <iostream>
#include "simplephysics.h"
//#include "tests.h"

#define DBG(msg) std::cout << msg <<std::endl;

int main(int, char**){
    PhysicsWorld world;

    vec2d origin = vec2d(0, 0);

    std::unique_ptr<Shape> shp1 = std::make_unique<Circle>(100);
    std::shared_ptr<RigidBody> bod1 = std::make_shared<RigidBody>(shp1,origin,1000);
    std::cout << bod1->m << std::endl;
    bod1->shape->setBody(bod1);
    bod1->moveto(vec2d(500,500));
    std::cout << bod1->m << std::endl;

    // std::vector<vec2d> verticies = {vec2d(0,0), vec2d(2,0), vec2d(2,-5), vec2d(3,1), vec2d(4,0), vec2d(1,1), vec2d()};

    // Poly poly = Poly(verticies);

    // for (unsigned int i = 0; i < poly.vertex_count; i++) {
    //     std::cout << "X: " << poly.vertex_list[i].x << "Y: " << poly.vertex_list[i].y << std::endl;
    // }


    // for (unsigned int i = 0; i < poly.vertex_count; i++) {
    //     std::cout << "X: " << poly.normals[i].x << "Y: " << poly.normals[i].y << std::endl;
    // }



    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow("OpenGL Test",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 800, SDL_WINDOW_OPENGL);
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear (renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderPresent(renderer);

    std::cin.get();

}
