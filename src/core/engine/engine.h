#ifndef ENGINE_H
#define ENGINE_H

#include "runtimedata.h"
#include "scene.h"
#include "world.h"
#include <unistd.h>

class Engine {
public:
    Engine();

    void createWorld();

    void createWorld(float g);

    void run();

    RunTimeData m_runtimedata;
    std::unique_ptr<World> m_world;
    std::unique_ptr<Scene> m_scene;
};

#endif // ENGINE_H
