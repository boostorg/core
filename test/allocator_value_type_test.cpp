/*
Copyright 2020 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#include <boost/core/allocator_access.hpp>
#include <boost/core/is_same.hpp>
#include <boost/core/lightweight_test_trait.hpp>

struct A {
    typedef int value_type;
};

int main()
{
    BOOST_TEST_TRAIT_TRUE((boost::core::is_same<int,
        boost::allocator_value_type<A>::type>));
    return boost::report_errors();
}
