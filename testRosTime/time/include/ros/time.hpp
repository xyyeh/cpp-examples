#ifndef DE588476_6D86_4433_B768_8DE16FB00838
#define DE588476_6D86_4433_B768_8DE16FB00838

// system
#include <sys/time.h>

#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/math/special_functions/round.hpp>
#include <cmath>
#include <iostream>

// lib related
#include <ros/duration.hpp>

namespace ros {

/*********************************************************************
 ** Exceptions
 *********************************************************************/

class Exception : public std::runtime_error {
public:
  Exception(const std::string &what) : std::runtime_error(what) {}
};

/**
 * @brief Thrown if the ros subsystem hasn't been initialised before use.
 */
class TimeNotInitializedException : public Exception {
public:
  TimeNotInitializedException()
      : Exception(
            "Cannot use ros::Time::now() before the first NodeHandle has been created or ros::start() has been called. "
            " "
            "If this is a standalone app or test that just uses ros::Time and does not communicate over ROS, you may "
            "also call ros::Time::init()") {}
};

/**
 * @brief Thrown if windoze high perf. timestamping is unavailable.
 *
 * @sa getWallTime
 */
class NoHighPerformanceTimersException : public Exception {
public:
  NoHighPerformanceTimersException()
      : Exception(
            "This windows platform does not "
            "support the high-performance timing api.") {}
};

/*********************************************************************
 ** Functions
 *********************************************************************/

void normalizeSecNSec(uint64_t &sec, uint64_t &nsec);
void normalizeSecNSec(uint32_t &sec, uint32_t &nsec);
void normalizeSecNSecUnsigned(int64_t &sec, int64_t &nsec);

/*********************************************************************
 ** Time Classes
 *********************************************************************/

/**
 * \brief Base class for Time implementations.  Provides storage, common functions and operator overloads.
 * This should not need to be used directly.
 */
template <class T, class D>
class TimeBase {
public:
  uint32_t sec, nsec;

  TimeBase() : sec(0), nsec(0) {}
  TimeBase(uint32_t _sec, uint32_t _nsec) : sec(_sec), nsec(_nsec) { normalizeSecNSec(sec, nsec); }
  explicit TimeBase(double t) { fromSec(t); }
  ~TimeBase() {}
  D operator-(const T &rhs) const;
  T operator+(const D &rhs) const;
  T operator-(const D &rhs) const;
  T &operator+=(const D &rhs);
  T &operator-=(const D &rhs);
  bool operator==(const T &rhs) const;
  inline bool operator!=(const T &rhs) const { return !(*static_cast<const T *>(this) == rhs); }
  bool operator>(const T &rhs) const;
  bool operator<(const T &rhs) const;
  bool operator>=(const T &rhs) const;
  bool operator<=(const T &rhs) const;

  double toSec() const { return (double)sec + 1e-9 * (double)nsec; };
  T &fromSec(double t) {
    sec = (uint32_t)floor(t);
    nsec = (uint32_t)boost::math::round((t - sec) * 1e9);
    return *static_cast<T *>(this);
  }

  uint64_t toNSec() const { return (uint64_t)sec * 1000000000ull + (uint64_t)nsec; }
  T &fromNSec(uint64_t t);

  inline bool isZero() const { return sec == 0 && nsec == 0; }
  inline bool is_zero() const { return isZero(); }
  boost::posix_time::ptime toBoost() const;
};

/**
 * \brief Time representation.  May either represent wall clock time or ROS clock time.
 *
 * ros::TimeBase provides most of its functionality.
 */
class Time : public TimeBase<Time, Duration> {
public:
  Time() : TimeBase<Time, Duration>() {}

  Time(uint32_t _sec, uint32_t _nsec) : TimeBase<Time, Duration>(_sec, _nsec) {}

  explicit Time(double t) { fromSec(t); }

  /**
   * \brief Retrieve the current time.  If ROS clock time is in use, this returns the time according to the
   * ROS clock.  Otherwise returns the current wall clock time.
   */
  static Time now();
  /**
   * \brief Sleep until a specific time has been reached.
   */
  static bool sleepUntil(const Time &end);

  static void init();
  static void shutdown();
  static void setNow(const Time &new_now);
  static bool useSystemTime();
  static bool isSimTime();
  static bool isSystemTime();

  /**
   * \brief Returns whether or not the current time is valid.  Time is valid if it is non-zero.
   */
  static bool isValid();
  /**
   * \brief Wait for time to become valid
   */
  static bool waitForValid();
  /**
   * \brief Wait for time to become valid, with timeout
   */
  static bool waitForValid(const ros::WallDuration &timeout);
};

extern const Time TIME_MAX;
extern const Time TIME_MIN;

/**
 * \brief Time representation.  Always wall-clock time.
 *
 * ros::TimeBase provides most of its functionality.
 */
class WallTime : public TimeBase<WallTime, WallDuration> {
public:
  WallTime() : TimeBase<WallTime, WallDuration>() {}

  WallTime(uint32_t _sec, uint32_t _nsec) : TimeBase<WallTime, WallDuration>(_sec, _nsec) {}

  explicit WallTime(double t) { fromSec(t); }

  /**
   * \brief Returns the current wall clock time.
   */
  static WallTime now();

  /**
   * \brief Sleep until a specific time has been reached.
   */
  static bool sleepUntil(const WallTime &end);

  static bool isSystemTime() { return true; }
};

std::ostream &operator<<(std::ostream &os, const Time &rhs);
std::ostream &operator<<(std::ostream &os, const WallTime &rhs);
}  // namespace ros

#endif /* DE588476_6D86_4433_B768_8DE16FB00838 */
