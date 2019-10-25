//  Copyright (c) 2019 Hans Dembinski
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/core/doc/html/core/version.html for documentation.
//
#ifndef BOOST_CORE_CLASS_VERSION_HPP
#define BOOST_CORE_CLASS_VERSION_HPP

#include <boost/config.hpp>

namespace boost {
namespace core {

template <int N>
struct int_c {
  typedef int value_type;
  enum { value = N };
  operator value_type() const { return N; }
};

} /* core */

// default implementation, to be specialized by users as needed
template <class T>
struct class_version : ::boost::core::int_c<0> {};

namespace serialization {

// for backward compatibility
template<class T>
struct version : ::boost::class_version<T> {};

} /* serialization */

} /* boost */

#define BOOST_CLASS_VERSION(T, N)                                          \
namespace boost {                                                          \
template <> struct class_version<T> : ::boost::core::int_c<N> {}; \
}

#endif
