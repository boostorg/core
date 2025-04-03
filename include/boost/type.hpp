// (C) Copyright David Abrahams 2001.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPE_DWA20010120_HPP
# define BOOST_TYPE_DWA20010120_HPP

#include <boost/core/detail/module_macro.hpp>

namespace boost {

BOOST_CORE_BEGIN_MODULE_EXPORT
  // Just a simple "type envelope". Useful in various contexts, mostly to work
  // around some MSVC deficiencies.
  template <class T>
  struct type {};

BOOST_CORE_END_MODULE_EXPORT

}

#endif // BOOST_TYPE_DWA20010120_HPP
