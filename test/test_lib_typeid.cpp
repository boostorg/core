
// Copyright 2018 Peter Dimov.
// Distributed under the Boost Software License, Version 1.0.

#include <boost/core/typeinfo.hpp>
#include <boost/core/lightweight_test.hpp>

boost::core::typeinfo const * get_typeid_int();

int main()
{
    BOOST_TEST_EQ( get_typeid_int(), &BOOST_CORE_TYPEID( int ) );
    return boost::report_errors();
}
