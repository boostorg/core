/*
Copyright 2020 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#include <boost/core/allocator_access.hpp>
#include <boost/core/lightweight_test.hpp>

struct A1 {
    typedef int* pointer;
    typedef int size_type;

    A1()
        : value() { }

    pointer allocate(size_type n) {
        value = n;
        return &value;
    }

    size_type value;
};

#if defined(BOOST_CORE_ALLOCATOR_DETECTION)
struct A2 {
    typedef int* pointer;
    typedef int size_type;

    A2()
        : value() { }

    pointer allocate(size_type n) {
        value = n;
        return &value;
    }

    pointer allocate(size_type n, const void*) {
        value = n + 1;
        return &value;
    }

    size_type value;
};
#endif

int main()
{
    {
        A1 a;
        BOOST_TEST_EQ(*boost::allocator_allocate(a, 1, 0), 1);
    }
#if defined(BOOST_CORE_ALLOCATOR_DETECTION)
    {
        A2 a;
        BOOST_TEST_EQ(*boost::allocator_allocate(a, 1, 0), 2);
    }
#endif
    return boost::report_errors();
}
