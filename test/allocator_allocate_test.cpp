/*
Copyright 2020 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#include <boost/core/allocator_access.hpp>
#include <boost/core/lightweight_test.hpp>

struct A {
    typedef int* pointer;
    typedef int size_type;

    A()
        : value() { }

    pointer allocate(size_type n) {
        value = n;
        return &value;
    }

    size_type value;
};

int main()
{
    A a;
    BOOST_TEST_EQ(*boost::allocator_allocate(a, 5), 5);
    return boost::report_errors();
}
