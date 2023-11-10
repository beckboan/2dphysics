#ifndef SCENE_H
#define SCENE_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"
#include "edge.h"
#include "rigidbody.h"
#include <memory>
#include <vector>

struct Scene {
  Scene(int screen_x_, int screen_y_);
  Scene(const Scene &other) = delete;
  Scene &operator=(const Scene &other) = delete;
  Scene(Scene &&other) = delete;
  Scene &operator=(Scene &&other) = delete;
  ~Scene();

  void drawBody(const std::shared_ptr<RigidBody> body);
  void drawAABB(const std::shared_ptr<RigidBody> body);
  void drawBoundary(const std::shared_ptr<Edge> edge);
  void drawObjects(const std::vector<std::shared_ptr<RigidBody>> bodies);
  void checkEvent();
  void init();
  void clear();
  bool getActive() { return is_active; }
  void setActive(bool b) { is_active = b; }

private:
  const int32_t screen_x;
  const int32_t screen_y;
  const int32_t hw_x;
  const int32_t hw_y;
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;
  SDL_Event e;
  bool is_active = 0;
  const int scale{20};
  int renderYTransfer(int y);
  int renderXTransfer(int x);
};

#endif
