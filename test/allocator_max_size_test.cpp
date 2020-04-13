/*
Copyright 2020 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#include <boost/core/allocator_access.hpp>
#include <boost/core/lightweight_test.hpp>

struct A1 {
    typedef long value_type;
    typedef short size_type;
};

#if defined(BOOST_CORE_ALLOCATOR_DETECTION)
struct A2 {
    typedef long value_type;
    typedef short size_type;

    size_type max_size() const {
        return 1;
    }
};
#endif

int main()
{
    BOOST_TEST_EQ(boost::allocator_max_size(A1()),
        std::numeric_limits<A1::size_type>::max() / sizeof(A1::value_type));
#if defined(BOOST_CORE_ALLOCATOR_DETECTION)
    BOOST_TEST_EQ(boost::allocator_max_size(A2()), 1);
#endif
    return boost::report_errors();
}
