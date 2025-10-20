#ifndef BOOST_CORE_STATIC_ASSERT_HPP_INCLUDED
#define BOOST_CORE_STATIC_ASSERT_HPP_INCLUDED

// Copyright 2025 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#if defined(__cpp_static_assert) && __cpp_static_assert >= 200410L

#define BOOST_CORE_STATIC_ASSERT(...) static_assert(__VA_ARGS__, #__VA_ARGS__)

#else

#include <boost/static_assert.hpp>

#define BOOST_CORE_STATIC_ASSERT(expr) BOOST_STATIC_ASSERT(expr)

#endif

#endif  // #ifndef BOOST_CORE_STATIC_ASSERT_HPP_INCLUDED
