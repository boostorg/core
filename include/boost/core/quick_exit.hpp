#ifndef BOOST_CORE_QUICK_EXIT_HPP_INCLUDED
#define BOOST_CORE_QUICK_EXIT_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//  boost/core/quick_exit.hpp
//
//  Copyright 2018 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <boost/config.hpp>
#include <cstdlib>

namespace boost
{

void quick_exit( int code )
{
    std::quick_exit( code );
}

} // namespace boost

#endif  // #ifndef BOOST_CORE_QUICK_EXIT_HPP_INCLUDED
