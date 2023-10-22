#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include "world.h"
#include "runtimedata.h"
#include <unistd.h>
#include "scene.h"


class Engine {
public:
    Engine();
    void createWorld();
    void createWorld(float g);
    void run();
    void renderObjects();

    RunTimeData m_runtimedata;
    std::unique_ptr<World> m_world;
    std::unique_ptr<Scene> m_scene;

};



#endif // !DEBUG
