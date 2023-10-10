#ifndef RUNTIMEDATA_H
#define RUNTIMEDATA_H

struct RunTimeData
{
    const float fps = 30;
    const float dt = 1/fps;
    float time_accumulation = 0;
    float frameStart = 0;
    float frameEnd = 0;
};

#endif // !RUNTIMEDATA_H
#define RUNTIMEDATA_H


