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
    typedef int* pointer;
};

struct A2 {
    typedef int* pointer;
    typedef bool* void_pointer;
};

int main()
{
    BOOST_TEST_TRAIT_TRUE((boost::core::is_same<void*,
        boost::allocator_void_pointer<A1>::type>));
    BOOST_TEST_TRAIT_TRUE((boost::core::is_same<bool*,
        boost::allocator_void_pointer<A2>::type>));
    return boost::report_errors();
}
