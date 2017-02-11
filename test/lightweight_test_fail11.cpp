//
// Negative test for BOOST_TEST_ALL_EQ
//
// Copyright (c) 2017 Bjorn Reese
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//

#include <vector>
#include <boost/core/lightweight_test.hpp>

int main()
{
    int test_cases = 0;

    {
        std::vector<int> x, y;
        x.push_back( 1 );
        BOOST_TEST_ALL_EQ( x.begin(), x.end(), y.begin(), y.end() );
        ++test_cases;
    }
    {
        std::vector<int> x, y;
        y.push_back( 1 );
        BOOST_TEST_ALL_EQ( x.begin(), x.end(), y.begin(), y.end() );
        ++test_cases;
    }

    {
        std::vector<int> x, y;
        x.push_back( 1 ); x.push_back( 2 ); x.push_back( 3 ); x.push_back( 4 );
        y.push_back( 1 ); y.push_back( 3 ); y.push_back( 2 ); y.push_back( 4 );
        BOOST_TEST_ALL_EQ( x.begin(), x.end(), y.begin(), y.end() );
        ++test_cases;
    }

    {
        std::vector<float> x, y;
        x.push_back( 1.0f ); x.push_back( 2.0f ); x.push_back( 3.0f ); x.push_back( 4.0f );
        y.push_back( 4.0f ); y.push_back( 2.0f ); y.push_back( 3.0f ); y.push_back( 1.0f );
        BOOST_TEST_ALL_EQ( x.begin(), x.end(), y.begin(), y.end() );
        ++test_cases;
    }

    boost::report_errors();

    return boost::detail::test_errors() == test_cases;
}
