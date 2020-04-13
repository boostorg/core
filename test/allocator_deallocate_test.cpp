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

    void deallocate(pointer, size_type n) {
        value = n;
    }

    size_type value;
};

int main()
{
    A a;
    boost::allocator_deallocate(a, 0, 5);
    BOOST_TEST_EQ(a.value, 5);
    return boost::report_errors();
}
