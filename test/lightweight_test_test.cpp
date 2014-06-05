//
// Test for lightweight_test.hpp
//
// Copyright (c) 2014 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//

#include <boost/detail/lightweight_test.hpp>

struct X
{
};

#if !defined( BOOST_NO_EXCEPTIONS )
# define LWT_THROW( x ) throw x
#else
# define LWT_THROW( x ) ((void)(x))
#endif

void f( bool x )
{
    if( x )
    {
        LWT_THROW( X() );
    }
    else
    {
        LWT_THROW( 5 );
    }
}

template<class T1, class T2> struct Y1
{
    enum { value = 1 };
};

template<class T1, class T2> struct Y2
{
    enum { value = 0 };
};

struct X1
{
    typedef int type;
};

struct X2
{
    typedef int type;
};

int main()
{
    int x = 0;

    // BOOST_TEST

    BOOST_TEST( x == 0 );
    BOOST_TEST( ++x == 1 );
    BOOST_TEST( x++ == 1 );
    BOOST_TEST( x == 2? true: false );
    BOOST_TEST( x == 2? &x: 0 );

    // BOOST_TEST_EQ

    BOOST_TEST_EQ( x, 2 );
    BOOST_TEST_EQ( ++x, 3 );
    BOOST_TEST_EQ( x++, 3 );

    int y = 4;

    BOOST_TEST_EQ( ++x, ++y );
    BOOST_TEST_EQ( x++, y++ );

    // BOOST_TEST_NE

    BOOST_TEST_NE( ++x, y );
    BOOST_TEST_NE( &x, &y );

    // BOOST_TEST_THROWS

    BOOST_TEST_THROWS( throw X(), X );
    BOOST_TEST_THROWS( throw 1, int );

    BOOST_TEST_THROWS( f(true), X );
    BOOST_TEST_THROWS( f(false), int );

    // BOOST_TEST_TRAIT_TRUE

    BOOST_TEST_TRAIT_TRUE(( Y1<X1::type, X2::type> ));

    // BOOST_TEST_TRAIT_FALSE

    BOOST_TEST_TRAIT_FALSE(( Y2<X1::type, X2::type> ));

    return boost::report_errors();
}
