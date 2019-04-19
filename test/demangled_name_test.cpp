//
// Trivial test for core::demangled_name
//
// Copyright (c) 2014 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//

#include <boost/core/typeinfo.hpp>
#include <iostream>

template<class T1, class T2> struct Y1
{
};

int main()
{
    typedef Y1<int, long> T;
    typedef T* TP;
    typedef T& TR;
    typedef T const TC;
    typedef T const * const TCPC;
    typedef T const & TCR;
    std::cout
        << '"' << boost::core::demangled_name( BOOST_CORE_TYPEID( T ) ) << "\"\n"
        << '"' << boost::core::demangled_name( BOOST_CORE_TYPEID( TP ) ) << "\"\n"
        << '"' << boost::core::demangled_name( BOOST_CORE_TYPEID( TR ) ) << "\"\n"
        << '"' << boost::core::demangled_name( BOOST_CORE_TYPEID( TC ) ) << "\"\n"
        << '"' << boost::core::demangled_name( BOOST_CORE_TYPEID( TCPC ) ) << "\"\n"
        << '"' << boost::core::demangled_name( BOOST_CORE_TYPEID( TCR ) ) << "\"\n"
        << std::flush;
    return 0;
}
