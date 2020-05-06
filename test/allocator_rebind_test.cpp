/*
Copyright 2020 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#include <boost/core/allocator_access.hpp>
#include <boost/core/is_same.hpp>
#include <boost/core/lightweight_test_trait.hpp>

template<class, class, class>
struct A1 { };

template<class, class U, class V>
struct A2 {
    template<class T>
    struct rebind {
        typedef A1<T, U, V> other;
    };
};

int main()
{
    BOOST_TEST_TRAIT_TRUE((boost::core::is_same<A1<bool, int, float>,
        boost::allocator_rebind<A1<char, int, float>, bool>::type>));
    BOOST_TEST_TRAIT_TRUE((boost::core::is_same<A1<bool, int, float>,
        boost::allocator_rebind<A2<char, int, float>, bool>::type>));
    return boost::report_errors();
}
