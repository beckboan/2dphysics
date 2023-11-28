#ifndef RUNTIMEDATA_H
#define RUNTIMEDATA_H

#include <chrono>

using namespace std::literals;

auto constexpr dt = 1.0s / 60;

struct RunTimeData {

  using Clock = std::chrono::steady_clock;
  using duration = std::chrono::duration<float>;
  using time_point = std::chrono::time_point<Clock, duration>;

  duration accumulator = 0s;
  float dt_f = 1.0 / 60;
  time_point curr_time = Clock::now();
  float getDTFloat() { return dt_f; }
  void updateClock();
  void updateInternalTimers();
  bool goPhysics() { return accumulator >= dt; }
};

#endif // !RUNTIMEDATA_H
