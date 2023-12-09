#include "engine.h"
#include <unistd.h>

int main(int argc, char *args[]) {
    Engine engine;
    engine.createWorld(9.8);

    vec2d position = vec2d(0.0, 0.0);
    float density = 1000.0;
    vec2d movetopos = vec2d(-300, 0);

    std::vector<vec2d> verticies = {vec2d(0, 0), vec2d(50, 0), vec2d(50, 50), vec2d(0, 50), vec2d(75, 100)};

    std::vector<vec2d> verticies_2 = {vec2d(0, 0), vec2d(10, 0), vec2d(10, 10), vec2d(0, 10), vec2d(15, 20), vec2d(-10, 10)};
    // engine.m_world->addCircle(10, position, 1000, 1);
    // engine.m_world->addCircle(10, vec2d(0, 100), 1000, 0);
    // engine.m_world->addPoly(verticies_2, vec2d(0, 0), density, 0);
    // engine.m_world->addPoly(verticies_2, vec2d(0, 25), density, 0);
    // engine.m_world->addPoly(verticies_2, vec2d(0, 50), density, 0);
    engine.m_world->addPoly(verticies_2, vec2d(0, 75), density, 0);
    // engine.m_world->addPoly(verticies_2, vec2d(0.0, 90.0), density, 0);
    // engine.m_world->addPoly(verticies, vec2d(0, 400), density, 0);
    engine.m_world->addEdge(vec2d(-200, -50), vec2d(500, -50));
    // engine.m_world->addCircle(10, vec2d(1, -100), 1000, 1);

    engine.run();
}
