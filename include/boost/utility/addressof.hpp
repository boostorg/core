// Copyright (C) 2002 Brad King (brad.king@kitware.com) 
//                    Doug Gregor (gregod@cs.rpi.edu)
//
// Permission to copy, use, sell and distribute this software is granted
// provided this copyright notice appears in all copies.
// Permission to modify the code and to distribute modified code is granted
// provided this copyright notice appears in all copies, and a notice
// that the code was modified is included with the copyright notice.
//
// This software is provided "as is" without express or implied warranty,
// and with no claim as to its suitability for any purpose.

// For more information, see http://www.boost.org

#ifndef BOOST_UTILITY_ADDRESSOF_HPP
#define BOOST_UTILITY_ADDRESSOF_HPP

namespace boost {

namespace detail {
  struct addressof_helper {}; 
}

template <typename T>
inline T* addressof(T& v)
{
  return reinterpret_cast<T*>(
	   &reinterpret_cast<detail::addressof_helper&>(v));
}

template <typename T>
inline const T* addressof(const T& v)
{
  return reinterpret_cast<const T*>(
           &reinterpret_cast<const detail::addressof_helper&>(v));
}

template <typename T>
inline volatile T* addressof(volatile T& v)
{
  return reinterpret_cast<volatile T*>(
           &reinterpret_cast<volatile detail::addressof_helper&>(v));
}

template <typename T>
inline const volatile T* addressof(const volatile T& v)
{
  return reinterpret_cast<const volatile T*>(
           &reinterpret_cast<const volatile detail::addressof_helper&>(v));
}

}

#endif // BOOST_UTILITY_ADDRESSOF_HPP
