#include "engine.h"

void Engine::run()
{
    m_world.renderObjects();
    m_world.worldStep(5);
    usleep(1000000);
    m_world.renderObjects();
}

