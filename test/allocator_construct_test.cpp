/*
Copyright 2020 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#include <boost/core/allocator_access.hpp>
#include <boost/core/default_allocator.hpp>
#include <boost/core/lightweight_test.hpp>

struct S {
    S(int v)
        : value(v) { }

    int value;
};

struct A1 { };

#if defined(BOOST_CORE_ALLOCATOR_DETECTION)
struct A2 {
    void construct(S* p, int v) {
        new(p) S(v + 1);
    }
};
#endif

int main()
{
    boost::default_allocator<S> d;
    {
        S* p = d.allocate(1);
        A1 a;
        boost::allocator_construct(a, p, 1);
        BOOST_TEST_EQ(p->value, 1);
        d.deallocate(p, 1);
    }
#if defined(BOOST_CORE_ALLOCATOR_DETECTION)
    {
        S* p = d.allocate(1);
        A2 a;
        boost::allocator_construct(a, p, 1);
        BOOST_TEST_EQ(p->value, 2);
        d.deallocate(p, 1);
    }
#endif
    return boost::report_errors();
}
