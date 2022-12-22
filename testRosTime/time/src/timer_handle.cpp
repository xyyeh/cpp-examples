#include "ros/timer_handle.h"

#include "ros/steady_timer_options.h"
#include "ros/timer_options.h"
#include "ros/wall_timer_options.h"

namespace ros {
Timer TimerHandle::createTimer(Duration period, const TimerCallback& callback, bool oneshot, bool autostart) const {
  TimerOptions ops;
  ops.period = period;
  ops.callback = callback;
  ops.oneshot = oneshot;
  ops.autostart = autostart;
  return createTimer(ops);
}

Timer TimerHandle::createTimer(TimerOptions& ops) const {
  if (ops.callback_queue == 0) {
    if (callback_queue_) {
      ops.callback_queue = callback_queue_;
    } else {
      std::cout << "TODO: Global queue not available" << std::endl;
    }
  }

  Timer timer(ops);
  if (ops.autostart) timer.start();
  return timer;
}

WallTimer TimerHandle::createWallTimer(WallDuration period, const WallTimerCallback& callback, bool oneshot,
                                       bool autostart) const {
  WallTimerOptions ops;
  ops.period = period;
  ops.callback = callback;
  ops.oneshot = oneshot;
  ops.autostart = autostart;
  return createWallTimer(ops);
}

WallTimer TimerHandle::createWallTimer(WallTimerOptions& ops) const {
  if (ops.callback_queue == 0) {
    if (callback_queue_) {
      ops.callback_queue = callback_queue_;
    } else {
      std::cout << "TODO: Global queue not available" << std::endl;
    }
  }

  WallTimer timer(ops);
  if (ops.autostart) timer.start();
  return timer;
}

SteadyTimer TimerHandle::createSteadyTimer(WallDuration period, const SteadyTimerCallback& callback, bool oneshot,
                                           bool autostart) const {
  SteadyTimerOptions ops;
  ops.period = period;
  ops.callback = callback;
  ops.oneshot = oneshot;
  ops.autostart = autostart;
  return createSteadyTimer(ops);
}

SteadyTimer TimerHandle::createSteadyTimer(SteadyTimerOptions& ops) const {
  if (ops.callback_queue == 0) {
    if (callback_queue_) {
      ops.callback_queue = callback_queue_;
    } else {
      std::cout << "TODO: Global queue not available" << std::endl;
    }
  }

  SteadyTimer timer(ops);
  if (ops.autostart) timer.start();
  return timer;
}

}  // namespace ros
