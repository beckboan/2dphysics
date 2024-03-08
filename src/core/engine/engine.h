#ifndef ENGINE_H
#define ENGINE_H

#include "runtimedata.h"
#include "world.h"
#include <unistd.h>

class Engine {
public:
    Engine();

    void run();

    void addTestParams() const;

    std::unique_ptr<World> m_world{nullptr};
private:
    RunTimeData m_runtimedata;
};

#endif // ENGINE_H
