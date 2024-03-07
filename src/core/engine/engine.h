#ifndef ENGINE_H
#define ENGINE_H

#include "runtimedata.h"
#include "world.h"
#include <unistd.h>

class Engine {
public:
    Engine();

    void createWorld();

    void createWorld(float g);

    void run();

    std::unique_ptr<World> m_world{nullptr};
    std::unique_ptr<Scene> m_scene{nullptr};
private:
    RunTimeData m_runtimedata;
};

#endif // ENGINE_H
