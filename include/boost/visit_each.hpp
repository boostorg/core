// Boost.Signals library

// Copyright Douglas Gregor 2001-2003. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org/libs/signals
#ifndef BOOST_VISIT_EACH_HPP
#define BOOST_VISIT_EACH_HPP

#if defined(BOOST_USE_MODULES) && !defined(BOOST_CORE_INTERFACE_UNIT)
#ifndef BOOST_IN_MODULE_PURVIEW
import boost.core;
#endif
#else

#include <boost/core/detail/modules.hpp>

namespace boost {
  BOOST_CORE_MODULE_EXPORT template<typename Visitor, typename T>
  inline void visit_each(Visitor& visitor, const T& t, long)
  {
    visitor(t);
  }

  BOOST_CORE_MODULE_EXPORT template<typename Visitor, typename T>
  inline void visit_each(Visitor& visitor, const T& t)
  {
    visit_each(visitor, t, 0);
  }
}

#endif

#endif // BOOST_VISIT_EACH_HPP
