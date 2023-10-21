#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include "world.h"
#include "runtimedata.h"

class Engine {
public:
    Engine();
    void init();
    void run();
private:
    RunTimeData m_runtimedata;
    std::unique_ptr<World> m_world;

};



#endif // !DEBUG
