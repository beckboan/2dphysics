#ifndef SCENE_H
#define SCENE_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"
#include "rigidbody.h"
#include <memory>

struct Scene
{
    Scene();

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    void drawBody(const std::shared_ptr<RigidBody> body);
};


#endif