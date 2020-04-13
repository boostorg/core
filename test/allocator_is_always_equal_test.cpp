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
    int value;
};

struct A2 {
    struct is_always_equal {
        BOOST_STATIC_CONSTEXPR bool value = true;
    };

    int value;
};

#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
struct A3 { };
#endif

int main()
{
    BOOST_TEST_TRAIT_FALSE((boost::allocator_is_always_equal<A1>::type));
    BOOST_TEST_TRAIT_TRUE((boost::allocator_is_always_equal<A2>::type));
#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
    BOOST_TEST_TRAIT_TRUE((boost::allocator_is_always_equal<A3>::type));
#endif
    return boost::report_errors();
}
