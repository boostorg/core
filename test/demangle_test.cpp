//
// Trivial test for core::demangle
//
// Copyright (c) 2014 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//

#include <boost/core/demangle.hpp>
#include <iostream>

template<class T1, class T2> struct Y1
{
};

int main()
{
    typedef Y1<int, long> T;
    std::cout << boost::core::demangle( typeid( T ).name() );
    return 0;
}
