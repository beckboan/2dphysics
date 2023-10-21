#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include "world.h"
#include "runtimedata.h"
#include <unistd.h>

class Engine {
public:
    Engine() {};
    void createWorld();
    void createWorld(float g);
    void run();
    RunTimeData m_runtimedata;
    World m_world;

};



#endif // !DEBUG
