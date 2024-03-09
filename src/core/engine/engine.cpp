#include "engine.h"

Engine::Engine() {
    world = std::make_unique<World>(9.8);
    addTestParams();
}

void Engine::clear() const {
    world->contact_list.clear();
    world->clearBodies();
}

void Engine::run() {
    runtimedata.updateClock();
    while (runtimedata.goPhysics()) {
        world->worldStep(runtimedata.getDTFloat());
        runtimedata.updateInternalTimers();
    }
}

void Engine::addTestParams() const {

    vec2d position = vec2d(0.0, 0.0);
    float density = 1000.0;

    std::vector<vec2d> verticies = {vec2d(0, 0), vec2d(50, 0), vec2d(50, 50), vec2d(0, 50), vec2d(75, 100)};

    std::vector<vec2d> box_verts = {vec2d(0, 0), vec2d(100, 0), vec2d(0, 100), vec2d(100, 100)};

    std::vector<vec2d> verticies_2 = {vec2d(0, 0), vec2d(10, 0), vec2d(10, 10), vec2d(0, 10), vec2d(15, 20),
                                      vec2d(-10, 5)};
    std::vector<vec2d> verticies_3 = {vec2d(0, 0), vec2d(10, 0), vec2d(10, 10), vec2d(0, 10), vec2d(15, 20)};

    world->addCircle(10, vec2d(0, 50), 500, false);
    //    world->addCircle(10, vec2d(5, 30), 1000, false);
    //    world->addCircle(10, vec2d(-5, 55), 1000, false);
    //    world->addCircle(10, vec2d(0, 90), 1000, false);
    //    world->addPoly(verticies_2, vec2d(0, -35), density, false);
    //    world->addPoly(verticies_2, vec2d(0, 60), density, false);
    //    world->addPoly(verticies_2, vec2d(0, 90), density, false);
    //    world->addPoly(verticies_2, vec2d(0, 120), density, false);
    world->addEdge(vec2d(-200, -50), vec2d(500, -50));
    world->addEdge(vec2d(-200, -50), vec2d(-200, 500));
    world->addEdge(vec2d(500, -50), vec2d(500, 500));
}

void Engine::addLevelParams() const {

}