/*
Copyright 2020 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#include <boost/core/allocator_access.hpp>
#include <boost/core/is_same.hpp>
#include <boost/core/lightweight_test_trait.hpp>

struct A1 { };

struct A2 {
    struct propagate_on_container_swap {
        BOOST_STATIC_CONSTEXPR bool value = true;
    };
};

int main()
{
    BOOST_TEST_TRAIT_FALSE((boost::
        allocator_propagate_on_container_swap<A1>::type));
    BOOST_TEST_TRAIT_TRUE((boost::
        allocator_propagate_on_container_swap<A2>::type));
    return boost::report_errors();
}
