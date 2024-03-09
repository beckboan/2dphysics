#ifndef ENGINE_H
#define ENGINE_H

#include "runtimedata.h"
#include "world.h"
#include <unistd.h>

class Engine {
public:
    Engine();

    void run();

    void clear() const;

    void addTestParams() const;

    void addLevelParams() const;

    std::unique_ptr<World> world{nullptr};
private:
    RunTimeData runtimedata;
};

#endif // ENGINE_H
