/*
Copyright 2022 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#include <boost/core/allocator_access.hpp>
#include <boost/core/lightweight_test.hpp>

template<class T>
struct A {
    typedef T value_type;
    A() { }
    template<class U>
    void destroy(U* p) {
        *p = U();
    }
};

int main()
{
    A<int> a;
    int i[3] = { 5, 5, 5 };
    boost::allocator_destroy_n(a, &i[0], 3);
    BOOST_TEST_EQ(i[0], 0);
    BOOST_TEST_EQ(i[1], 0);
    BOOST_TEST_EQ(i[2], 0);
    return boost::report_errors();
}
