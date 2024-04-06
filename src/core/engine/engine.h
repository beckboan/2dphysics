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

    void addLevelParams(const std::string &filename);

    void refreshLevelParams();

    std::unique_ptr<World> world{nullptr};

private:
    std::string curr_level_path;
    RunTimeData runtimedata;
    std::string level_name = "NA";
};

#endif// ENGINE_H
