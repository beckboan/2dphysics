#include "runtimedata.h"

void RunTimeData::updateClock() {
  time_point new_time = Clock::now();
  auto frame_time = new_time - curr_time;
  if (frame_time > 0.1s)
    frame_time = 0.1s;
  curr_time = new_time;

  accumulator += frame_time;
}

void RunTimeData::updateInternalTimers() {
  t += dt;
  accumulator -= dt;
}
