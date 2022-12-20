#ifndef C8E53EEB_A9D3_4902_898B_F85867F38267
#define C8E53EEB_A9D3_4902_898B_F85867F38267

#include <sys/time.h>

#include <boost/date_time/posix_time/posix_time.hpp>

// lib related
#include <ros/time.hpp>

namespace ros {

template <class T, class D>
T &TimeBase<T, D>::fromNSec(uint64_t t) {
  sec = (int32_t)(t / 1000000000);
  nsec = (int32_t)(t % 1000000000);

  normalizeSecNSec(sec, nsec);

  return *static_cast<T *>(this);
}

template <class T, class D>
D TimeBase<T, D>::operator-(const T &rhs) const {
  return D((int32_t)sec - (int32_t)rhs.sec,
           (int32_t)nsec - (int32_t)rhs.nsec);  // carry handled in ctor
}

template <class T, class D>
T TimeBase<T, D>::operator-(const D &rhs) const {
  return *static_cast<const T *>(this) + (-rhs);
}

template <class T, class D>
T TimeBase<T, D>::operator+(const D &rhs) const {
  int64_t sec_sum = (int64_t)sec + (int64_t)rhs.sec;
  int64_t nsec_sum = (int64_t)nsec + (int64_t)rhs.nsec;

  // Throws an exception if we go out of 32-bit range
  normalizeSecNSecUnsigned(sec_sum, nsec_sum);

  // now, it's safe to downcast back to uint32 bits
  return T((uint32_t)sec_sum, (uint32_t)nsec_sum);
}

template <class T, class D>
T &TimeBase<T, D>::operator+=(const D &rhs) {
  *this = *this + rhs;
  return *static_cast<T *>(this);
}

template <class T, class D>
T &TimeBase<T, D>::operator-=(const D &rhs) {
  *this += (-rhs);
  return *static_cast<T *>(this);
}

template <class T, class D>
bool TimeBase<T, D>::operator==(const T &rhs) const {
  return sec == rhs.sec && nsec == rhs.nsec;
}

template <class T, class D>
bool TimeBase<T, D>::operator<(const T &rhs) const {
  if (sec < rhs.sec)
    return true;
  else if (sec == rhs.sec && nsec < rhs.nsec)
    return true;
  return false;
}

template <class T, class D>
bool TimeBase<T, D>::operator>(const T &rhs) const {
  if (sec > rhs.sec)
    return true;
  else if (sec == rhs.sec && nsec > rhs.nsec)
    return true;
  return false;
}

template <class T, class D>
bool TimeBase<T, D>::operator<=(const T &rhs) const {
  if (sec < rhs.sec)
    return true;
  else if (sec == rhs.sec && nsec <= rhs.nsec)
    return true;
  return false;
}

template <class T, class D>
bool TimeBase<T, D>::operator>=(const T &rhs) const {
  if (sec > rhs.sec)
    return true;
  else if (sec == rhs.sec && nsec >= rhs.nsec)
    return true;
  return false;
}

template <class T, class D>
boost::posix_time::ptime TimeBase<T, D>::toBoost() const {
  namespace pt = boost::posix_time;
#if defined(BOOST_DATE_TIME_HAS_NANOSECONDS)
  return pt::from_time_t(sec) + pt::nanoseconds(nsec);
#else
  return pt::from_time_t(sec) + pt::microseconds(static_cast<int>(nsec / 1000.0));
#endif
}

}  // namespace ros

#endif /* C8E53EEB_A9D3_4902_898B_F85867F38267 */
