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
    static int count;

    S() {
        ++count;
    }

    S(const S&) {
        ++count;
    }

    ~S() {
        --count;
    }
};

int S::count = 0;

struct A1 { };

#if defined(BOOST_CORE_ALLOCATOR_DETECTION)
struct A2 {
    void destroy(S*) {
        ++S::count;
    }
};
#endif

int main()
{
    boost::default_allocator<S> d;
    {
        S* p = d.allocate(1);
        new(p) S;
        A1 a;
        boost::allocator_destroy(a, p);
        BOOST_TEST_EQ(S::count, 0);
        d.deallocate(p, 1);
    }
#if defined(BOOST_CORE_ALLOCATOR_DETECTION)
    {
        S* p = d.allocate(1);
        new(p) S;
        A2 a;
        boost::allocator_destroy(a, p);
        BOOST_TEST_EQ(S::count, 2);
        d.deallocate(p, 1);
    }
#endif
    return boost::report_errors();
}
