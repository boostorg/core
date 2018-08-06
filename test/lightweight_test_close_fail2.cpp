//
// Negative test for BOOST_TEST_CLOSE
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
    const double x = 0.1;
    BOOST_TEST_CLOSE( x, 0, 0, 0.05 );

    return boost::report_errors();
}
