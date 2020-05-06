/*
Copyright 2020 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#include <boost/core/allocator_access.hpp>
#include <boost/core/is_same.hpp>
#include <boost/core/lightweight_test_trait.hpp>

#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
struct A1 {
    typedef long difference_type;
};
#else
struct A1 {
    typedef unsigned long size_type;
};
#endif

struct A2 {
    typedef long difference_type;
    typedef unsigned short size_type;
};

int main()
{
    BOOST_TEST_TRAIT_TRUE((boost::core::is_same<unsigned long,
        boost::allocator_size_type<A1>::type>));
    BOOST_TEST_TRAIT_TRUE((boost::core::is_same<unsigned short,
        boost::allocator_size_type<A2>::type>));
    return boost::report_errors();
}
