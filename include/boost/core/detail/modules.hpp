//
//  Copyright (c) 2025 Ruben Perez Hidalgo
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_CORE_DETAIL_MODULES_HPP
#define BOOST_CORE_DETAIL_MODULES_HPP

// BOOST_CORE_MODULE_EXPORT

#ifdef BOOST_USE_MODULES
#  define BOOST_CORE_MODULE_EXPORT export
#else
#  define BOOST_CORE_MODULE_EXPORT
#endif

#endif
