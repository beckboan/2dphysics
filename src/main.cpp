#include "engine.h"
#include <unistd.h>

int main(int argc, char *args[]) {
    Engine engine;
    engine.createWorld(9.8);

    vec2d position = vec2d(0.0, 0.0);
    float density = 1000.0;
    vec2d movetopos = vec2d(-300, 0);

    std::vector<vec2d> verticies = {vec2d(0, 0), vec2d(50, 0), vec2d(50, 50), vec2d(0, 50), vec2d(75, 100)};

    std::vector<vec2d> box_verts = {vec2d(0, 0), vec2d(100, 0), vec2d(0, 100), vec2d(100, 100)};

    std::vector<vec2d> verticies_2 = {vec2d(0, 0), vec2d(10, 0), vec2d(10, 10), vec2d(0, 10), vec2d(15, 20), vec2d(-10, 5)};
    std::vector<vec2d> verticies_3 = {vec2d(0, 0), vec2d(10, 0), vec2d(10, 10), vec2d(0, 10), vec2d(15, 20)};
    engine.m_world->addCircle(10, vec2d(0, 5), 1000, 0);
    engine.m_world->addCircle(10, vec2d(5, 30), 1000, 0);
    engine.m_world->addCircle(10, vec2d(-5, 55), 1000, 0);
    engine.m_world->addCircle(10, vec2d(0, 80), 1000, 0);
    engine.m_world->addPoly(verticies_3, vec2d(0, -15), density, 0);
    //    engine.m_world->addCircle(10, vec2d(20, 5), 1000, 0);
    // engine.m_world->addCircle(10, vec2d(25, 30), 1000, 0);
    engine.m_world->addPoly(verticies_2, vec2d(0, -35), density, 0);
    engine.m_world->addPoly(verticies_2, vec2d(0, 60), density, 0);
    // engine.m_world->addPoly(verticies_3, vec2d(0, 10), density, 0);
    // engine.m_world->addPoly(verticies_3, vec2d(0, 40), density, 0);
    // engine.m_world->addPoly(verticies_3, vec2d(0, 65), density, 0);
    // engine.m_world->addPoly(verticies_2, vec2d(0, 50), density, 0);
    // engine.m_world->addPoly(verticies_2, vec2d(0, 75), density, 0);
    // engine.m_world->addPoly(verticies_2, vec2d(0.0, 90.0), density, 0);
    // engine.m_world->addPoly(box_verts, vec2d(0, 0), density, 1);
    engine.m_world->addEdge(vec2d(-200, -50), vec2d(500, -50));
    engine.m_world->addEdge(vec2d(-200, -50), vec2d(-200, 500));
    engine.m_world->addEdge(vec2d(500, -50), vec2d(500, 500));
    // engine.m_world->addCircle(10, vec2d(1, -100), 1000, 1);

    engine.run();
}
