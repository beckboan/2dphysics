#include "engine.h"

void Engine::createWorld()
{
    m_world = std::make_unique<World>();
}

void Engine::createWorld(float g)
{
    m_world = std::make_unique<World>(g);
}

void Engine::run()
{
    m_world->renderObjects();
    m_world->worldStep(5);
    usleep(1000000);
    m_world->renderObjects();
}

