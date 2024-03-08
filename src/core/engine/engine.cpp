#include "engine.h"

Engine::Engine() {
    m_world = std::make_unique<World>(9.8);
    addTestParams();
}


void Engine::addTestParams() const {

    vec2d position = vec2d(0.0, 0.0);
    float density = 1000.0;

    std::vector<vec2d> verticies = {vec2d(0, 0), vec2d(50, 0), vec2d(50, 50), vec2d(0, 50), vec2d(75, 100)};

    std::vector<vec2d> box_verts = {vec2d(0, 0), vec2d(100, 0), vec2d(0, 100), vec2d(100, 100)};

    std::vector<vec2d> verticies_2 = {vec2d(0, 0), vec2d(10, 0), vec2d(10, 10), vec2d(0, 10), vec2d(15, 20),
                                      vec2d(-10, 5)};
    std::vector<vec2d> verticies_3 = {vec2d(0, 0), vec2d(10, 0), vec2d(10, 10), vec2d(0, 10), vec2d(15, 20)};

    m_world->addCircle(10, vec2d(0, 50), 500, false);
    //    m_world->addCircle(10, vec2d(5, 30), 1000, false);
    //    m_world->addCircle(10, vec2d(-5, 55), 1000, false);
    //    m_world->addCircle(10, vec2d(0, 90), 1000, false);
    //    m_world->addPoly(verticies_2, vec2d(0, -35), density, false);
    //    m_world->addPoly(verticies_2, vec2d(0, 60), density, false);
    //    m_world->addPoly(verticies_2, vec2d(0, 90), density, false);
    //    m_world->addPoly(verticies_2, vec2d(0, 120), density, false);
    m_world->addEdge(vec2d(-200, -50), vec2d(500, -50));
    m_world->addEdge(vec2d(-200, -50), vec2d(-200, 500));
    m_world->addEdge(vec2d(500, -50), vec2d(500, 500));
}

void Engine::run() {
    m_runtimedata.updateClock();
    while (m_runtimedata.goPhysics()) {
        m_world->worldStep(m_runtimedata.getDTFloat());
        m_runtimedata.updateInternalTimers();
    }
}
