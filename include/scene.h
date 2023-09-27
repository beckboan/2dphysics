#ifndef SCENE_H
#define SCENE_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"
#include "rigidbody.h"
#include <memory>

struct Scene
{
    Scene(int screen_x_, int screen_y_);
    

    void drawBody(const std::shared_ptr<RigidBody> body);
    void drawAABB(const std::shared_ptr<RigidBody> body);
    void init();

    private:    
    const int32_t screen_x;
    const int32_t screen_y;
    const int32_t hw_x;
    const int32_t hw_y;
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    const int scale {20};
    int renderYTransfer(int y);
    int renderXTransfer(int x);
};

#endif