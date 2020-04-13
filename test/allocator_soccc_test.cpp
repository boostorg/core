/*
Copyright 2020 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#include <boost/core/allocator_access.hpp>
#include <boost/core/lightweight_test.hpp>

struct A1 {
    A1(int v)
        : value(v) { }

    int value;
};

#if defined(BOOST_CORE_ALLOCATOR_DETECTION)
struct A2 {
    A2(int v)
        : value(v) { }

    A2 select_on_container_copy_construction() const {
        return A2(value + 1);
    }

    int value;
};
#endif

int main()
{
    BOOST_TEST_EQ(1,
        boost::allocator_select_on_container_copy_construction(A1(1)).value);
#if defined(BOOST_CORE_ALLOCATOR_DETECTION)
    BOOST_TEST_EQ(2,
        boost::allocator_select_on_container_copy_construction(A2(1)).value);
#endif
    return boost::report_errors();
}
