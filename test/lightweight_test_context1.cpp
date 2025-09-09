//
// Negative test for BOOST_TEST
//
// Copyright (c) 2014 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//

#include <cstring>
#include <iostream>
#include <sstream>
#include <string>

static std::stringstream test_log; // Intercept logging

#define BOOST_LIGHTWEIGHT_TEST_OSTREAM ::test_log
#include <boost/core/lightweight_test.hpp>

static bool check_log(const char* expected)
{
    std::string str = test_log.str();
    std::string::size_type pos = str.find('\n');
    std::string substr;
    if (pos != std::string::npos) {
        substr = str.substr(pos + 1);
    }
    if (substr != expected) {
        std::cerr << "Error: expected the following log:\n" << expected << "\n, got:\n" << substr << std::endl;
        return false;
    }
    return true;
}

int main()
{
    // Run a test that fails
    int x = 42;
    boost::core::lwt_context frame (&x);
    BOOST_TEST( x == 1 );

    // Check the log
    const char* const expected_log = "Failure happened in the following context:\n    #0: '42'\n";
    bool log_ok = check_log(expected_log);
    
    // Check that we get the number of expected errors
    int actual_errors = boost::report_errors();
    const int expected_errors = 1;
    if (actual_errors != expected_errors)
    {
        std::cerr << "Expected " << expected_errors << ", got " << actual_errors << " errors\n";
        return 1;
    }

    return log_ok ? 0 : 1;
}
