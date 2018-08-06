//
// Test for BOOST_TEST_CLOSE
//
// Copyright 2018 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//

#include <boost/core/lightweight_test.hpp>

int main()
{
    float x = 1.002;

    BOOST_TEST_CLOSE( x  , 1, 0.003, 0 );
    BOOST_TEST_CLOSE( 2*x, 2, 0.003, 0 );
    BOOST_TEST_CLOSE( x--, 1, 0, 0.005 );
    BOOST_TEST_CLOSE( x, 0, 0, 0.005 );

    int y = 0;

    BOOST_TEST_CLOSE( ++y, ++x, 0, 0.005 );
    BOOST_TEST_CLOSE( y++, x++, 0, 0.005 );

    return boost::report_errors();
}
