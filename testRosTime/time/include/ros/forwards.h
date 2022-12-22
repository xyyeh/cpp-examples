#ifndef B3F59226_27F2_4ACE_8FFB_24CFDCE1ADAB
#define B3F59226_27F2_4ACE_8FFB_24CFDCE1ADAB

#include <ros/time.h>

#include <boost/function.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace ros {

typedef boost::shared_ptr<void> VoidPtr;
typedef boost::weak_ptr<void> VoidWPtr;
typedef boost::shared_ptr<void const> VoidConstPtr;
typedef boost::weak_ptr<void const> VoidConstWPtr;

class CallbackQueue;
class CallbackQueueInterface;
class CallbackInterface;
typedef boost::shared_ptr<CallbackInterface> CallbackInterfacePtr;

class TimerOperations;
typedef boost::shared_ptr<TimerOperations> TimerOperationsPtr;

/**
 * \brief Structure passed as a parameter to the callback invoked by a ros::Timer
 */
struct TimerEvent {
  Time last_expected;  ///< In a perfect world, this is when the last callback should have happened
  Time last_real;      ///< When the last callback actually happened
  Time last_expired;   ///< When the last timer actually expired and the callback was added to the queue

  Time current_expected;  ///< In a perfect world, this is when the current callback should be happening
  Time current_real;  ///< This is when the current callback was actually called (Time::now() as of the beginning of the
                      ///< callback)
  Time current_expired;  ///< When the current timer actually expired and the callback was added to the queue

  struct {
    WallDuration last_duration;  ///< How long the last callback ran for
  } profile;
};
typedef boost::function<void(const TimerEvent&)> TimerCallback;

/**
 * \brief Structure passed as a parameter to the callback invoked by a ros::WallTimer
 */
struct WallTimerEvent {
  WallTime last_expected;  ///< In a perfect world, this is when the last callback should have happened
  WallTime last_real;      ///< When the last callback actually happened
  WallTime last_expired;   ///< When the last timer actually expired and the callback was added to the queue

  WallTime current_expected;  ///< In a perfect world, this is when the current callback should be happening
  WallTime current_real;  ///< This is when the current callback was actually called (Time::now() as of the beginning of
                          ///< the callback)
  WallTime current_expired;  ///< When the current timer actually expired and the callback was added to the queue

  struct {
    WallDuration last_duration;  ///< How long the last callback ran for
  } profile;
};
typedef boost::function<void(const WallTimerEvent&)> WallTimerCallback;

// /**
//  * \brief Structure passed as a parameter to the callback invoked by a ros::SteadyTimer
//  */
// struct SteadyTimerEvent {
//   SteadyTime last_expected;  ///< In a perfect world, this is when the last callback should have happened
//   SteadyTime last_real;      ///< When the last callback actually happened
//   SteadyTime last_expired;   ///< When the last timer actually expired and the callback was added to the queue

//   SteadyTime current_expected;  ///< In a perfect world, this is when the current callback should be happening
//   SteadyTime current_real;      ///< This is when the current callback was actually called (SteadyTime::now() as of
//   the
//                                 ///< beginning of the callback)
//   SteadyTime current_expired;   ///< When the current timer actually expired and the callback was added to the queue

//   struct {
//     WallDuration last_duration;  ///< How long the last callback ran for
//   } profile;
// };
// typedef boost::function<void(const SteadyTimerEvent&)> SteadyTimerCallback;
}  // namespace ros

#endif /* B3F59226_27F2_4ACE_8FFB_24CFDCE1ADAB */
