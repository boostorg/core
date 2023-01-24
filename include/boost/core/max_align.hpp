#ifndef BOOST_CORE_MAX_ALIGN_HPP_INCLUDED
#define BOOST_CORE_MAX_ALIGN_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//  Copyright 2023 Peter Dimov
//  Distributed under the Boost Software License, Version 1.0.
//  https://www.boost.org/LICENSE_1_0.txt

#include <boost/config.hpp>
#include <cstddef>

namespace boost
{
namespace core
{

union max_align_t
{
    char c;
    short s;
    int i;
    long l;

#if !defined(BOOST_NO_LONG_LONG)

    boost::long_long_type ll;

#endif

#if defined(BOOST_HAS_INT128)

    boost::int128_type i128;

#endif

    float f;
    double d;
    long double ld;

#if defined(BOOST_HAS_FLOAT128) || defined(__SIZEOF_FLOAT128__)

    __float128 f128;

#endif

    void* p;
    void (*pf) ();

    int max_align_t::* pm;
    void (max_align_t::*pmf)();
};

#if !defined(BOOST_NO_CXX11_ALIGNOF)

BOOST_CONSTEXPR_OR_CONST std::size_t max_align = alignof( max_align_t );

#elif defined(__GNUC__)

BOOST_CONSTEXPR_OR_CONST std::size_t max_align = __alignof__( max_align_t );

#elif defined(_MSC_VER)

BOOST_CONSTEXPR_OR_CONST std::size_t max_align = __alignof( max_align_t );

#else

namespace detail
{

struct alignment_of_helper
{
    char x;
    max_align_t a;
};

} // namespace detail

BOOST_CONSTEXPR_OR_CONST std::size_t max_align = offsetof( core::detail::alignment_of_helper, a );

#endif

} // namespace core
} // namespace boost

#endif  // #ifndef BOOST_CORE_MAX_ALIGN_HPP_INCLUDED
