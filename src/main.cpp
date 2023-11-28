#include "engine.h"
#include <unistd.h>

#define DBG(msg) std::cout << msg << std::endl;

int main(int argc, char *args[]) {
  Engine engine;
  engine.createWorld(9.8);

  vec2d position = vec2d(0.0, 0.0);
  float density = 1000.0;
  vec2d movetopos = vec2d(-300, 0);

  std::vector<vec2d> verticies = {vec2d(0, 0), vec2d(50, 0), vec2d(50, 50),
                                  vec2d(0, 50), vec2d(75, 100)};

  std::vector<vec2d> verticies_2 = {vec2d(0, 0), vec2d(10, 0), vec2d(10, 10),
                                    vec2d(0, 10), vec2d(15, 20)};
  // engine.m_world->addCircle(10, position, 1000, 1);
  // engine.m_world->addCircle(10, vec2d(0, 100), 1000, 0);
  engine.m_world->addPoly(verticies, position, 10, 1);
  engine.m_world->addPoly(verticies, vec2d(0.0, 90.0), 10, 0);
  // engine.m_world->addPoly(verticies, vec2d(0, 400), 1000, 0);
  // engine.m_world->addEdge(vec2d(-200, -400), vec2d(400, -400), 1);
  // engine.m_world->addCircle(10, vec2d(1, -100), 1000, 1);

  engine.run();
}
