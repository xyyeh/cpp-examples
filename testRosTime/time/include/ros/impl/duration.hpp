#ifndef FA831DFB_DB3F_4AA6_BA83_AF77599E2D85
#define FA831DFB_DB3F_4AA6_BA83_AF77599E2D85

#include <boost/date_time/posix_time/posix_time_types.hpp>

// lib related
#include <ros/duration.hpp>
#include <ros/rate.hpp>

namespace ros {
//
// DurationBase template member function implementation
//
template <class T>
DurationBase<T>::DurationBase(int32_t _sec, int32_t _nsec) : sec(_sec), nsec(_nsec) {
  normalizeSecNSecSigned(sec, nsec);
}

template <class T>
T &DurationBase<T>::fromSec(double d) {
#ifdef HAVE_TRUNC
  sec = (int32_t)trunc(d);
#else
  // (morgan: why doesn't win32 provide trunc? argh. hacked this together
  // without much thought. need to test this conversion.
  if (d >= 0.0)
    sec = (int32_t)floor(d);
  else
    sec = (int32_t)floor(d) + 1;
#endif
  nsec = (int32_t)((d - (double)sec) * 1000000000);
  return *static_cast<T *>(this);
}

template <class T>
T &DurationBase<T>::fromNSec(int64_t t) {
  sec = (int32_t)(t / 1000000000);
  nsec = (int32_t)(t % 1000000000);

  normalizeSecNSecSigned(sec, nsec);

  return *static_cast<T *>(this);
}

template <class T>
T DurationBase<T>::operator+(const T &rhs) const {
  return T(sec + rhs.sec, nsec + rhs.nsec);
}

template <class T>
T DurationBase<T>::operator*(double scale) const {
  return T(toSec() * scale);
}

template <class T>
T DurationBase<T>::operator-(const T &rhs) const {
  return T(sec - rhs.sec, nsec - rhs.nsec);
}

template <class T>
T DurationBase<T>::operator-() const {
  return T(-sec, -nsec);
}

template <class T>
T &DurationBase<T>::operator+=(const T &rhs) {
  *this = *this + rhs;
  return *static_cast<T *>(this);
}

template <class T>
T &DurationBase<T>::operator-=(const T &rhs) {
  *this += (-rhs);
  return *static_cast<T *>(this);
}

template <class T>
T &DurationBase<T>::operator*=(double scale) {
  fromSec(toSec() * scale);
  return *static_cast<T *>(this);
}

template <class T>
bool DurationBase<T>::operator<(const T &rhs) const {
  if (sec < rhs.sec)
    return true;
  else if (sec == rhs.sec && nsec < rhs.nsec)
    return true;
  return false;
}

template <class T>
bool DurationBase<T>::operator>(const T &rhs) const {
  if (sec > rhs.sec)
    return true;
  else if (sec == rhs.sec && nsec > rhs.nsec)
    return true;
  return false;
}

template <class T>
bool DurationBase<T>::operator<=(const T &rhs) const {
  if (sec < rhs.sec)
    return true;
  else if (sec == rhs.sec && nsec <= rhs.nsec)
    return true;
  return false;
}

template <class T>
bool DurationBase<T>::operator>=(const T &rhs) const {
  if (sec > rhs.sec)
    return true;
  else if (sec == rhs.sec && nsec >= rhs.nsec)
    return true;
  return false;
}

template <class T>
bool DurationBase<T>::operator==(const T &rhs) const {
  return sec == rhs.sec && nsec == rhs.nsec;
}

template <class T>
bool DurationBase<T>::isZero() {
  return sec == 0 && nsec == 0;
}

template <class T>
boost::posix_time::time_duration DurationBase<T>::toBoost() const {
  namespace bt = boost::posix_time;
#if defined(BOOST_DATE_TIME_HAS_NANOSECONDS)
  return bt::seconds(sec) + bt::nanoseconds(nsec);
#else
  return bt::seconds(sec) + bt::microseconds(static_cast<int>(nsec / 1000.0));
#endif
}

inline Duration::Duration(const Rate &r) { fromSec(r.expectedCycleTime().toSec()); }

inline WallDuration::WallDuration(const Rate &r) { fromSec(r.expectedCycleTime().toSec()); }

}  // namespace ros

#endif /* FA831DFB_DB3F_4AA6_BA83_AF77599E2D85 */
