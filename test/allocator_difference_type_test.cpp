/*
Copyright 2020 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#include <boost/core/allocator_access.hpp>
#include <boost/core/is_same.hpp>
#include <boost/core/lightweight_test_trait.hpp>

struct A1 {
    typedef char* pointer;
};

struct A2 {
    typedef char* pointer;
    typedef int difference_type;
};

int main()
{
    BOOST_TEST_TRAIT_TRUE((boost::core::is_same<std::ptrdiff_t,
        boost::allocator_difference_type<A1>::type>));
    BOOST_TEST_TRAIT_TRUE((boost::core::is_same<int,
        boost::allocator_difference_type<A2>::type>));
    return boost::report_errors();
}
