/*
Copyright 2024 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#include <boost/core/pointer_in_range.hpp>
#include <boost/static_assert.hpp>

#if !defined(BOOST_CORE_NO_CONSTEXPR_POINTER_IN_RANGE)
int a[4] = { 0, 0, 0, 0 };
int n = 0;
const int b[4] = { 0, 0, 0, 0 };
const int m = 0;

BOOST_STATIC_ASSERT(!boost::pointer_in_range(&a[1], &a[0], a + 4));
BOOST_STATIC_ASSERT(boost::pointer_in_range(&a[1], &a[1], a + 4));
BOOST_STATIC_ASSERT(boost::pointer_in_range(&a[1], &a[2], a + 4));
BOOST_STATIC_ASSERT(boost::pointer_in_range(&a[1], &a[3], a + 4));
BOOST_STATIC_ASSERT(!boost::pointer_in_range(&a[1], a + 4, a + 4));
BOOST_STATIC_ASSERT(!boost::pointer_in_range(&a[0], &n, &a[3]));
BOOST_STATIC_ASSERT(!boost::pointer_in_range(&a[0], &m, &a[3]));
BOOST_STATIC_ASSERT(!boost::pointer_in_range(&b[1], &b[0], b + 4));
BOOST_STATIC_ASSERT(boost::pointer_in_range(&b[1], &b[1], b + 4));
BOOST_STATIC_ASSERT(boost::pointer_in_range(&b[1], &b[2], b + 4));
BOOST_STATIC_ASSERT(boost::pointer_in_range(&b[1], &b[3], b + 4));
BOOST_STATIC_ASSERT(!boost::pointer_in_range(&b[1], b + 4, b + 4));
BOOST_STATIC_ASSERT(!boost::pointer_in_range(&b[0], &n, &b[3]));
BOOST_STATIC_ASSERT(!boost::pointer_in_range(&b[0], &m, &b[3]));
#endif
