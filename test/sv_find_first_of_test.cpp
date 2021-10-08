// Copyright 2021 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/core/string_view.hpp>
#include <boost/core/lightweight_test.hpp>
#include <cstddef>

int main()
{
    std::size_t const npos = boost::core::string_view::npos;

    {
        boost::core::string_view sv( "" );

        BOOST_TEST_EQ( sv.find_first_of( boost::core::string_view() ), npos );
        BOOST_TEST_EQ( sv.find_first_of( boost::core::string_view(), 1 ), npos );

        BOOST_TEST_EQ( sv.find_first_of( boost::core::string_view( "" ) ), npos );
        BOOST_TEST_EQ( sv.find_first_of( boost::core::string_view( "" ), 1 ), npos );

        BOOST_TEST_EQ( sv.find_first_of( boost::core::string_view( "1" ) ), npos );
        BOOST_TEST_EQ( sv.find_first_of( boost::core::string_view( "1" ), 1 ), npos );

        BOOST_TEST_EQ( sv.find_first_of( '1' ), npos );
        BOOST_TEST_EQ( sv.find_first_of( '1', 1 ), npos );

        BOOST_TEST_EQ( sv.find_first_of( "" ), npos );
        BOOST_TEST_EQ( sv.find_first_of( "", 1 ), npos );

        BOOST_TEST_EQ( sv.find_first_of( "1" ), npos );
        BOOST_TEST_EQ( sv.find_first_of( "1", 1 ), npos );

        BOOST_TEST_EQ( sv.find_first_of( "12", 0, 0 ), npos );
        BOOST_TEST_EQ( sv.find_first_of( "12", 1, 0 ), npos );

        BOOST_TEST_EQ( sv.find_first_of( "12", 0, 1 ), npos );
        BOOST_TEST_EQ( sv.find_first_of( "12", 1, 1 ), npos );

        BOOST_TEST_EQ( sv.find_first_of( "12", 0, 2 ), npos );
        BOOST_TEST_EQ( sv.find_first_of( "12", 1, 2 ), npos );
    }

    {
        boost::core::string_view sv( "123123" );

        BOOST_TEST_EQ( sv.find_first_of( boost::core::string_view() ), npos );
        BOOST_TEST_EQ( sv.find_first_of( boost::core::string_view(), 1 ), npos );
        BOOST_TEST_EQ( sv.find_first_of( boost::core::string_view(), 6 ), npos );
        BOOST_TEST_EQ( sv.find_first_of( boost::core::string_view(), 7 ), npos );

        BOOST_TEST_EQ( sv.find_first_of( boost::core::string_view( "" ) ), npos );
        BOOST_TEST_EQ( sv.find_first_of( boost::core::string_view( "" ), 1 ), npos );
        BOOST_TEST_EQ( sv.find_first_of( boost::core::string_view( "" ), 6 ), npos );
        BOOST_TEST_EQ( sv.find_first_of( boost::core::string_view( "" ), 7 ), npos );

        BOOST_TEST_EQ( sv.find_first_of( boost::core::string_view( "1" ) ), 0 );
        BOOST_TEST_EQ( sv.find_first_of( boost::core::string_view( "1" ), 1 ), 3 );
        BOOST_TEST_EQ( sv.find_first_of( boost::core::string_view( "1" ), 2 ), 3 );
        BOOST_TEST_EQ( sv.find_first_of( boost::core::string_view( "1" ), 3 ), 3 );
        BOOST_TEST_EQ( sv.find_first_of( boost::core::string_view( "1" ), 4 ), npos );
        BOOST_TEST_EQ( sv.find_first_of( boost::core::string_view( "1" ), 5 ), npos );
        BOOST_TEST_EQ( sv.find_first_of( boost::core::string_view( "1" ), 6 ), npos );
        BOOST_TEST_EQ( sv.find_first_of( boost::core::string_view( "1" ), 7 ), npos );

        BOOST_TEST_EQ( sv.find_first_of( boost::core::string_view( "4" ) ), npos );
        BOOST_TEST_EQ( sv.find_first_of( boost::core::string_view( "4" ), 1 ), npos );
        BOOST_TEST_EQ( sv.find_first_of( boost::core::string_view( "4" ), 6 ), npos );
        BOOST_TEST_EQ( sv.find_first_of( boost::core::string_view( "4" ), 7 ), npos );

        BOOST_TEST_EQ( sv.find_first_of( boost::core::string_view( "23" ) ), 1 );
        BOOST_TEST_EQ( sv.find_first_of( boost::core::string_view( "23" ), 1 ), 1 );
        BOOST_TEST_EQ( sv.find_first_of( boost::core::string_view( "23" ), 2 ), 2 );
        BOOST_TEST_EQ( sv.find_first_of( boost::core::string_view( "23" ), 3 ), 4 );
        BOOST_TEST_EQ( sv.find_first_of( boost::core::string_view( "23" ), 4 ), 4 );
        BOOST_TEST_EQ( sv.find_first_of( boost::core::string_view( "23" ), 5 ), 5 );
        BOOST_TEST_EQ( sv.find_first_of( boost::core::string_view( "23" ), 6 ), npos );
        BOOST_TEST_EQ( sv.find_first_of( boost::core::string_view( "23" ), 7 ), npos );

        BOOST_TEST_EQ( sv.find_first_of( '1' ), 0 );
        BOOST_TEST_EQ( sv.find_first_of( '1', 1 ), 3 );
        BOOST_TEST_EQ( sv.find_first_of( '1', 2 ), 3 );
        BOOST_TEST_EQ( sv.find_first_of( '1', 3 ), 3 );
        BOOST_TEST_EQ( sv.find_first_of( '1', 4 ), npos );
        BOOST_TEST_EQ( sv.find_first_of( '1', 5 ), npos );
        BOOST_TEST_EQ( sv.find_first_of( '1', 6 ), npos );
        BOOST_TEST_EQ( sv.find_first_of( '1', 7 ), npos );

        BOOST_TEST_EQ( sv.find_first_of( '3' ), 2 );
        BOOST_TEST_EQ( sv.find_first_of( '3', 1 ), 2 );
        BOOST_TEST_EQ( sv.find_first_of( '3', 2 ), 2 );
        BOOST_TEST_EQ( sv.find_first_of( '3', 3 ), 5 );
        BOOST_TEST_EQ( sv.find_first_of( '3', 4 ), 5 );
        BOOST_TEST_EQ( sv.find_first_of( '3', 5 ), 5 );
        BOOST_TEST_EQ( sv.find_first_of( '3', 6 ), npos );
        BOOST_TEST_EQ( sv.find_first_of( '3', 7 ), npos );

        BOOST_TEST_EQ( sv.find_first_of( '9' ), npos );

        BOOST_TEST_EQ( sv.find_first_of( "" ), npos );
        BOOST_TEST_EQ( sv.find_first_of( "", 1 ), npos );
        BOOST_TEST_EQ( sv.find_first_of( "", 6 ), npos );
        BOOST_TEST_EQ( sv.find_first_of( "", 7 ), npos );

        BOOST_TEST_EQ( sv.find_first_of( "1" ), 0 );
        BOOST_TEST_EQ( sv.find_first_of( "1", 1 ), 3 );
        BOOST_TEST_EQ( sv.find_first_of( "1", 2 ), 3 );
        BOOST_TEST_EQ( sv.find_first_of( "1", 3 ), 3 );
        BOOST_TEST_EQ( sv.find_first_of( "1", 4 ), npos );
        BOOST_TEST_EQ( sv.find_first_of( "1", 5 ), npos );
        BOOST_TEST_EQ( sv.find_first_of( "1", 6 ), npos );
        BOOST_TEST_EQ( sv.find_first_of( "1", 7 ), npos );

        BOOST_TEST_EQ( sv.find_first_of( "23" ), 1 );
        BOOST_TEST_EQ( sv.find_first_of( "23", 1 ), 1 );
        BOOST_TEST_EQ( sv.find_first_of( "23", 2 ), 2 );
        BOOST_TEST_EQ( sv.find_first_of( "23", 3 ), 4 );
        BOOST_TEST_EQ( sv.find_first_of( "23", 4 ), 4 );
        BOOST_TEST_EQ( sv.find_first_of( "23", 5 ), 5 );
        BOOST_TEST_EQ( sv.find_first_of( "23", 6 ), npos );
        BOOST_TEST_EQ( sv.find_first_of( "23", 7 ), npos );

        BOOST_TEST_EQ( sv.find_first_of( "123", 0, 0 ), npos );
        BOOST_TEST_EQ( sv.find_first_of( "123", 1, 0 ), npos );
        BOOST_TEST_EQ( sv.find_first_of( "123", 2, 0 ), npos );
        BOOST_TEST_EQ( sv.find_first_of( "123", 3, 0 ), npos );
        BOOST_TEST_EQ( sv.find_first_of( "123", 4, 0 ), npos );
        BOOST_TEST_EQ( sv.find_first_of( "123", 5, 0 ), npos );
        BOOST_TEST_EQ( sv.find_first_of( "123", 6, 0 ), npos );
        BOOST_TEST_EQ( sv.find_first_of( "123", 7, 0 ), npos );

        BOOST_TEST_EQ( sv.find_first_of( "123", 0, 1 ), 0 );
        BOOST_TEST_EQ( sv.find_first_of( "123", 1, 1 ), 3 );
        BOOST_TEST_EQ( sv.find_first_of( "123", 2, 1 ), 3 );
        BOOST_TEST_EQ( sv.find_first_of( "123", 3, 1 ), 3 );
        BOOST_TEST_EQ( sv.find_first_of( "123", 4, 1 ), npos );
        BOOST_TEST_EQ( sv.find_first_of( "123", 5, 1 ), npos );
        BOOST_TEST_EQ( sv.find_first_of( "123", 6, 1 ), npos );
        BOOST_TEST_EQ( sv.find_first_of( "123", 7, 1 ), npos );

        BOOST_TEST_EQ( sv.find_first_of( "123", 0, 2 ), 0 );
        BOOST_TEST_EQ( sv.find_first_of( "123", 1, 2 ), 1 );
        BOOST_TEST_EQ( sv.find_first_of( "123", 2, 2 ), 3 );
        BOOST_TEST_EQ( sv.find_first_of( "123", 3, 2 ), 3 );
        BOOST_TEST_EQ( sv.find_first_of( "123", 4, 2 ), 4 );
        BOOST_TEST_EQ( sv.find_first_of( "123", 5, 2 ), npos );
        BOOST_TEST_EQ( sv.find_first_of( "123", 6, 2 ), npos );
        BOOST_TEST_EQ( sv.find_first_of( "123", 7, 2 ), npos );

        BOOST_TEST_EQ( sv.find_first_of( "123", 0, 3 ), 0 );
        BOOST_TEST_EQ( sv.find_first_of( "123", 1, 3 ), 1 );
        BOOST_TEST_EQ( sv.find_first_of( "123", 2, 3 ), 2 );
        BOOST_TEST_EQ( sv.find_first_of( "123", 3, 3 ), 3 );
        BOOST_TEST_EQ( sv.find_first_of( "123", 4, 3 ), 4 );
        BOOST_TEST_EQ( sv.find_first_of( "123", 5, 3 ), 5 );
        BOOST_TEST_EQ( sv.find_first_of( "123", 6, 3 ), npos );
        BOOST_TEST_EQ( sv.find_first_of( "123", 7, 3 ), npos );
    }

    return boost::report_errors();
}
