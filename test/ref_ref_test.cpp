//
// Test for ref(ref(x))
//
// Copyright 2014 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//

#include <boost/ref.hpp>
#include <boost/core/lightweight_test.hpp>

int main()
{
    int x = 0;

    {
        boost::reference_wrapper< int > r = boost::ref( boost::ref( x ) );
        BOOST_TEST_EQ( &r.get(), &x );
    }

    {
        boost::reference_wrapper< int const > r = boost::ref( boost::cref( x ) );
        BOOST_TEST_EQ( &r.get(), &x );
    }

    {
        boost::reference_wrapper< int const > r = boost::cref( boost::ref( x ) );
        BOOST_TEST_EQ( &r.get(), &x );
    }

    {
        boost::reference_wrapper< int const > r = boost::cref( boost::cref( x ) );
        BOOST_TEST_EQ( &r.get(), &x );
    }

    return boost::report_errors();
}
