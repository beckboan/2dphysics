#include "engine.h"

Engine::Engine()
{
    int x = 1800;
    int y = 1000;
    m_scene = std::make_unique<Scene>(x, y);
    m_scene->init();
}
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
    std::cout << m_scene->getActive() << std::endl;
    while(m_scene->getActive())
    {
        m_scene->drawObjects(m_world->getBodies());
        m_world->worldStep(5);
        usleep(1000000);
        m_scene->drawObjects(m_world->getBodies());
    }
    
}

