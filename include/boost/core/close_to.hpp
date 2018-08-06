#ifndef BOOST_CORE_CLOSE_TO_HPP_INCLUDED
#define BOOST_CORE_CLOSE_TO_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

// close_to<T> returns true when arguments deviate within a tolerance
//
// Copyright 2018 Bjørn Reese, Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#include <cmath> // std::abs
#include <limits>
#include <algorithm> // std::max

namespace boost
{

namespace core
{

template <class T>
struct close_to
{
    close_to(T relative_tolerance = std::numeric_limits<T>::epsilon(),
             T absolute_tolerance = T(0))
        : relative(relative_tolerance),
          absolute(absolute_tolerance)
    {}

    bool operator() (const T& lhs, const T& rhs)
    {
        return std::abs(lhs - rhs) <= std::max(relative * std::max(std::abs(lhs), std::abs(rhs)), absolute);
    }

private:
    T relative;
    T absolute;
};

} // namespace core

} // namespace boost

#endif // #ifndef BOOST_CORE_CLOSE_TO_HPP_INCLUDED
