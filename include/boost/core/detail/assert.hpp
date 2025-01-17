/*
Copyright 2025 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_CORE_DETAIL_ASSERT_HPP
#define BOOST_CORE_DETAIL_ASSERT_HPP

#include <cassert>

#if !defined(NDEBUG) && \
    !defined(__clang__) && \
    !defined(__INTEL_COMPILER) && \
    defined(__GNUC__) && \
    (__GNUC__ < 5)
#define BOOST_CORE_ASSERT(expr) \
   ((expr) ? void(0) : __assert_fail(#expr, __FILE__, __LINE__, 0))
#else
#define BOOST_CORE_ASSERT(expr) assert(expr)
#endif

#endif
