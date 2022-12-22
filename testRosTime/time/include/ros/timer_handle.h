#include <boost/bind.hpp>

#include "ros/callback_queue_interface.h"
#include "ros/forwards.h"
#include "ros/rate.h"
#include "ros/steady_timer.h"
#include "ros/timer.h"
#include "ros/wall_timer.h"

namespace ros {

class TimerHandle {
public:
  TimerHandle(/* args */) = delete;
  ~TimerHandle() = delete;

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Versions of createTimer()
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /**
   * \brief Create a timer which will call a callback at the specified rate.  This variant takes
   * a class member function, and a bare pointer to the object to call the method on.
   *
   * When the Timer (and all copies of it) returned goes out of scope, the timer will automatically
   * be stopped, and the callback will no longer be called.
   *
   * \param r The rate at which to call the callback
   * \param callback The method to call
   * \param obj The object to call the method on
   * \param oneshot If true, this timer will only fire once
   * \param autostart If true (default), return timer that is already started
   */
  template <class Handler, class Obj>
  Timer createTimer(Rate r, Handler h, Obj o, bool oneshot = false, bool autostart = true) const {
    return createTimer(r.expectedCycleTime(), h, o, oneshot, autostart);
  }

  /**
   * \brief Create a timer which will call a callback at the specified rate.  This variant takes
   * a class member function, and a bare pointer to the object to call the method on.
   *
   * When the Timer (and all copies of it) returned goes out of scope, the timer will automatically
   * be stopped, and the callback will no longer be called.
   *
   * \param period The period at which to call the callback
   * \param callback The method to call
   * \param obj The object to call the method on
   * \param oneshot If true, this timer will only fire once
   * \param autostart If true (default), return timer that is already started
   */
  template <class T>
  Timer createTimer(Duration period, void (T::*callback)(const TimerEvent&) const, T* obj, bool oneshot = false,
                    bool autostart = true) const {
    return createTimer(period, boost::bind(callback, obj, boost::placeholders::_1), oneshot, autostart);
  }

  /**
   * \brief Create a timer which will call a callback at the specified rate.  This variant takes
   * a class member function, and a bare pointer to the object to call the method on.
   *
   * When the Timer (and all copies of it) returned goes out of scope, the timer will automatically
   * be stopped, and the callback will no longer be called.
   *
   * \param period The period at which to call the callback
   * \param callback The method to call
   * \param obj The object to call the method on
   * \param oneshot If true, this timer will only fire once
   * \param autostart If true (default), return timer that is already started
   */
  template <class T>
  Timer createTimer(Duration period, void (T::*callback)(const TimerEvent&), T* obj, bool oneshot = false,
                    bool autostart = true) const {
    return createTimer(period, boost::bind(callback, obj, boost::placeholders::_1), oneshot, autostart);
  }

  /**
   * \brief Create a timer which will call a callback at the specified rate.  This variant takes
   * a class member function, and a shared pointer to the object to call the method on.
   *
   * When the Timer (and all copies of it) returned goes out of scope, the timer will automatically
   * be stopped, and the callback will no longer be called.
   *
   * \param period The period at which to call the callback
   * \param callback The method to call
   * \param obj The object to call the method on.  Since this is a shared pointer, the object will
   * automatically be tracked with a weak_ptr so that if it is deleted before the Timer goes out of
   * scope the callback will no longer be called (and therefore will not crash).
   * \param oneshot If true, this timer will only fire once
   * \param autostart If true (default), return timer that is already started
   */
  template <class T>
  Timer createTimer(Duration period, void (T::*callback)(const TimerEvent&), const boost::shared_ptr<T>& obj,
                    bool oneshot = false, bool autostart = true) const {
    TimerOptions ops(period, boost::bind(callback, obj.get(), boost::placeholders::_1), 0);
    ops.tracked_object = obj;
    ops.oneshot = oneshot;
    ops.autostart = autostart;
    return createTimer(ops);
  }

  /**
   * \brief Create a timer which will call a callback at the specified rate.  This variant takes
   * anything that can be bound to a Boost.Function, including a bare function
   *
   * When the Timer (and all copies of it) returned goes out of scope, the timer will automatically
   * be stopped, and the callback will no longer be called.
   *
   * \param period The period at which to call the callback
   * \param callback The function to call
   * \param oneshot If true, this timer will only fire once
   * \param autostart If true (default), return timer that is already started
   */
  Timer createTimer(Duration period, const TimerCallback& callback, bool oneshot = false, bool autostart = true) const;

  /**
   * \brief Create a timer which will call a callback at the specified rate.  This variant allows
   * the full range of TimerOptions.
   *
   * When the Timer (and all copies of it) returned goes out of scope, the timer will automatically
   * be stopped, and the callback will no longer be called.
   *
   * \param ops The options to use when creating the timer
   */
  Timer createTimer(TimerOptions& ops) const;

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Versions of createWallTimer()
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////

  /**
   * \brief Create a timer which will call a callback at the specified rate, using wall time to determine
   * when to call the callback instead of ROS time.
   * This variant takes a class member function, and a bare pointer to the object to call the method on.
   *
   * When the Timer (and all copies of it) returned goes out of scope, the timer will automatically
   * be stopped, and the callback will no longer be called.
   *
   * \param period The period at which to call the callback
   * \param callback The method to call
   * \param obj The object to call the method on
   * \param oneshot If true, this timer will only fire once
   * \param autostart If true (default), return timer that is already started
   */
  template <class T>
  WallTimer createWallTimer(WallDuration period, void (T::*callback)(const WallTimerEvent&), T* obj,
                            bool oneshot = false, bool autostart = true) const {
    return createWallTimer(period, boost::bind(callback, obj, boost::placeholders::_1), oneshot, autostart);
  }

  /**
   * \brief Create a timer which will call a callback at the specified rate, using wall time to determine
   * when to call the callback instead of ROS time.  This variant takes
   * a class member function, and a shared pointer to the object to call the method on.
   *
   * When the Timer (and all copies of it) returned goes out of scope, the timer will automatically
   * be stopped, and the callback will no longer be called.
   *
   * \param period The period at which to call the callback
   * \param callback The method to call
   * \param obj The object to call the method on.  Since this is a shared pointer, the object will
   * automatically be tracked with a weak_ptr so that if it is deleted before the Timer goes out of
   * scope the callback will no longer be called (and therefore will not crash).
   * \param oneshot If true, this timer will only fire once
   */
  template <class T>
  WallTimer createWallTimer(WallDuration period, void (T::*callback)(const WallTimerEvent&),
                            const boost::shared_ptr<T>& obj, bool oneshot = false, bool autostart = true) const {
    WallTimerOptions ops(period, boost::bind(callback, obj.get(), boost::placeholders::_1), 0);
    ops.tracked_object = obj;
    ops.oneshot = oneshot;
    ops.autostart = autostart;
    return createWallTimer(ops);
  }

  /**
   * \brief Create a timer which will call a callback at the specified rate, using wall time to determine
   * when to call the callback instead of ROS time.  This variant takes
   * anything that can be bound to a Boost.Function, including a bare function
   *
   * When the Timer (and all copies of it) returned goes out of scope, the timer will automatically
   * be stopped, and the callback will no longer be called.
   *
   * \param period The period at which to call the callback
   * \param callback The function to call
   * \param oneshot If true, this timer will only fire once
   */
  WallTimer createWallTimer(WallDuration period, const WallTimerCallback& callback, bool oneshot = false,
                            bool autostart = true) const;

  /**
   * \brief Create a timer which will call a callback at the specified rate, using wall time to determine
   * when to call the callback instead of ROS time.  This variant allows
   * the full range of TimerOptions.
   *
   * When the Timer (and all copies of it) returned goes out of scope, the timer will automatically
   * be stopped, and the callback will no longer be called.
   *
   * \param ops The options to use when creating the timer
   */
  WallTimer createWallTimer(WallTimerOptions& ops) const;

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Versions of createSteadyTimer()
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////

  /**
   * \brief Create a timer which will call a callback at the specified rate, using wall time to determine
   * when to call the callback instead of ROS time.
   * This variant takes a class member function, and a bare pointer to the object to call the method on.
   *
   * When the Timer (and all copies of it) returned goes out of scope, the timer will automatically
   * be stopped, and the callback will no longer be called.
   *
   * \param period The period at which to call the callback
   * \param callback The method to call
   * \param obj The object to call the method on
   * \param oneshot If true, this timer will only fire once
   * \param autostart If true (default), return timer that is already started
   */
  template <class T>
  SteadyTimer createSteadyTimer(WallDuration period, void (T::*callback)(const SteadyTimerEvent&), T* obj,
                                bool oneshot = false, bool autostart = true) const {
    return createSteadyTimer(period, boost::bind(callback, obj, boost::placeholders::_1), oneshot, autostart);
  }

  /**
   * \brief Create a timer which will call a callback at the specified rate, using wall time to determine
   * when to call the callback instead of ROS time.  This variant takes
   * a class member function, and a shared pointer to the object to call the method on.
   *
   * When the Timer (and all copies of it) returned goes out of scope, the timer will automatically
   * be stopped, and the callback will no longer be called.
   *
   * \param period The period at which to call the callback
   * \param callback The method to call
   * \param obj The object to call the method on.  Since this is a shared pointer, the object will
   * automatically be tracked with a weak_ptr so that if it is deleted before the Timer goes out of
   * scope the callback will no longer be called (and therefore will not crash).
   * \param oneshot If true, this timer will only fire once
   */
  template <class T>
  SteadyTimer createSteadyTimer(WallDuration period, void (T::*callback)(const SteadyTimerEvent&),
                                const boost::shared_ptr<T>& obj, bool oneshot = false, bool autostart = true) const {
    SteadyTimerOptions ops(period, boost::bind(callback, obj.get(), boost::placeholders::_1), 0);
    ops.tracked_object = obj;
    ops.oneshot = oneshot;
    ops.autostart = autostart;
    return createSteadyTimer(ops);
  }

  /**
   * \brief Create a timer which will call a callback at the specified rate, using wall time to determine
   * when to call the callback instead of ROS time.  This variant takes
   * anything that can be bound to a Boost.Function, including a bare function
   *
   * When the Timer (and all copies of it) returned goes out of scope, the timer will automatically
   * be stopped, and the callback will no longer be called.
   *
   * \param period The period at which to call the callback
   * \param callback The function to call
   * \param oneshot If true, this timer will only fire once
   */
  SteadyTimer createSteadyTimer(WallDuration period, const SteadyTimerCallback& callback, bool oneshot = false,
                                bool autostart = true) const;

  /**
   * \brief Create a timer which will call a callback at the specified rate, using wall time to determine
   * when to call the callback instead of ROS time.  This variant allows
   * the full range of TimerOptions.
   *
   * When the Timer (and all copies of it) returned goes out of scope, the timer will automatically
   * be stopped, and the callback will no longer be called.
   *
   * \param ops The options to use when creating the timer
   */
  SteadyTimer createSteadyTimer(SteadyTimerOptions& ops) const;

private:
  CallbackQueueInterface* callback_queue_;
};

}  // namespace ros
