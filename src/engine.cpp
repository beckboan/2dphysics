#include "engine.h"

Engine::Engine() {
  int x = 1800;
  int y = 1000;
  m_scene = std::make_unique<Scene>(x, y);
  m_scene->init();
}
void Engine::createWorld() { m_world = std::make_unique<World>(); }

void Engine::createWorld(float g) { m_world = std::make_unique<World>(g); }

void Engine::run() {
  while (m_scene->getActive()) {
    m_runtimedata.updateClock();
    m_scene->checkEvent();
    while (m_runtimedata.goPhysics()) {
      m_world->worldStep(m_runtimedata.getDTFloat());
      m_runtimedata.updateInternalTimers();
    }

    m_scene->drawObjects(m_world->getBodies());
  }
}
