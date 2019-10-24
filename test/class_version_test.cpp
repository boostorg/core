//  Copyright (c) 2019 Hans Dembinski
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/core/doc/html/core/version.html for documentation.
//
#include <boost/core/class_version.hpp>
#include <boost/core/lightweight_test.hpp>

void test_int_c()
{
    typedef boost::core::int_c<2> two;
    char a[two::value];
    BOOST_TEST_EQ(sizeof(a), 2);
}

struct foo {};
struct bar {};

namespace boost {
template <> struct version<bar> : core::int_c<2> {};
}

void test_version()
{
    BOOST_TEST_EQ(boost::version<foo>::value, 0);
    BOOST_TEST_EQ(boost::version<bar>::value, 2);
}

struct baz {};
BOOST_CLASS_VERSION(baz, 3);

void test_macro()
{
    BOOST_TEST_EQ(boost::version<baz>::value, 3);
}

int main()
{
    test_int_c();
    test_version();
    test_macro();
    return boost::report_errors();
}
