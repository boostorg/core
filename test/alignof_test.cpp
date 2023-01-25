// Copyright 2023 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/core/alignof.hpp>
#include <boost/core/lightweight_test.hpp>
#include <boost/type_traits.hpp>
#include <boost/config.hpp>
#include <cstddef>

template<class T> struct struct_of
{
    T t;
};

template<class T> union union_of
{
    T t;
};

template<class T> void test2()
{
    BOOST_TEST_EQ( BOOST_CORE_ALIGNOF(T), boost::alignment_of<T>::value );

#if !defined(BOOST_NO_CXX11_ALIGNOF)

    BOOST_TEST_EQ( BOOST_CORE_ALIGNOF(T), alignof(T) );

#endif
}

template<class T> void test()
{
    test2<T>();
    test2<T[2]>();
    test2< struct_of<T> >();
    test2< union_of<T> >();
}

struct X
{
};

int main()
{
    test<char>();
    test<short>();
    test<int>();
    test<long>();

#if !defined(BOOST_NO_LONG_LONG)

    test<boost::long_long_type>();

#endif

#if defined(BOOST_HAS_INT128)

    test<boost::int128_type>();

#endif

    test<float>();
    test<double>();
    test<long double>();

#if defined(BOOST_HAS_FLOAT128)

    test<__float128>();

#endif

    test<void*>();
    test<void(*)()>();

#if !defined(_MSC_VER)

    // under MSVC, alignof is 8, boost::alignment_of is 4
    // under clang-cl, alignof is 4, boost::alignment_of is 8 (!)

    test<int X::*>();

#endif

    test<void (X::*)()>();

    return boost::report_errors();
}
