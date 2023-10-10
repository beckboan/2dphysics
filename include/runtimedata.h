#ifndef RUNTIMEDATA_H
#define RUNTIMEDATA_H

#include <chrono>
#include <iostream>

struct RunTimeData
{
  const float fps = 30;
  const float dt = 1/fps;
  float time_accumulation = 0;
  float frameStart = 0;
  float frameEnd = 0;

  void updateClock() {}
  void startClocK() {}
  void stopClock() {}
  void pauseClock() {}
};

#endif // !RUNTIMEDATA_H


