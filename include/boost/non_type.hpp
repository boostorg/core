// -------------------------------------
//
//           (C) Copyright Gennaro Prota 2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// ------------------------------------------------------

#ifndef BOOST_NON_TYPE_HPP_GP_20030417
#define BOOST_NON_TYPE_HPP_GP_20030417

#if defined(BOOST_USE_MODULES) && !defined(BOOST_CORE_INTERFACE_UNIT)
#ifndef BOOST_IN_MODULE_PURVIEW
import boost.core;
#endif
#else

#include <boost/core/detail/modules.hpp>

namespace boost {

  // Just a simple "envelope" for non-type template parameters. Useful
  // to work around some MSVC deficiencies.

 BOOST_CORE_MODULE_EXPORT template <typename T, T n>
 struct non_type { };


}

#endif

#endif // include guard
