#ifndef SCENE_H
#define SCENE_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"
#include "rigidbody.h"
#include <memory>
#include <vector>

struct Scene
{
    Scene(int screen_x_, int screen_y_);
    ~Scene();
    
    void drawBody(const std::shared_ptr<RigidBody> body);
    void drawAABB(const std::shared_ptr<RigidBody> body);
    void drawObjects(const std::vector<std::shared_ptr<RigidBody>> bodies);
    void init();
    void clear();
    bool getActive() {return is_active;}

    private:    
    const int32_t screen_x;
    const int32_t screen_y;
    const int32_t hw_x;
    const int32_t hw_y;
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_Event e;
    bool is_active = 0;
    const int scale {20};
    int renderYTransfer(int y);
    int renderXTransfer(int x);
};

#endif
