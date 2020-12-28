#ifndef BOOST_CORE_BIT_HPP_INCLUDED
#define BOOST_CORE_BIT_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

// boost/core/bit.hpp
//
// A portable version of the C++20 standard header <bit>
//
// Copyright 2020 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/config.hpp>
#include <boost/static_assert.hpp>
#include <limits>
#include <cstring>

#define BOOST_CORE_BIT_CONSTEXPR

namespace boost
{
namespace core
{

// bit_cast
template<class To, class From>
To bit_cast( From const & from) BOOST_NOEXCEPT
{
    BOOST_STATIC_ASSERT( sizeof(To) == sizeof(From) );

    To to;
    std::memcpy( &to, &from, sizeof(To) );
    return to;
}

// counting
template<class T>
BOOST_CORE_BIT_CONSTEXPR int countl_zero( T x ) BOOST_NOEXCEPT;

template<class T>
BOOST_CORE_BIT_CONSTEXPR int countl_one( T x ) BOOST_NOEXCEPT
{
    return boost::core::countl_zero( ~x );
}

template<class T>
BOOST_CORE_BIT_CONSTEXPR int countr_zero( T x ) BOOST_NOEXCEPT;

template<class T>
BOOST_CORE_BIT_CONSTEXPR int countr_one( T x ) BOOST_NOEXCEPT
{
    return boost::core::countr_zero( ~x );
}

template<class T>
BOOST_CORE_BIT_CONSTEXPR int popcount( T x ) BOOST_NOEXCEPT;

// rotating
template<class T>
BOOST_CXX14_CONSTEXPR T rotl( T x, int s ) BOOST_NOEXCEPT
{
    unsigned const mask = std::numeric_limits<T>::digits - 1;
    return x << (s & mask) | x >> ((-s) & mask);
}

template<class T>
BOOST_CXX14_CONSTEXPR T rotr( T x, int s ) BOOST_NOEXCEPT
{
    unsigned const mask = std::numeric_limits<T>::digits - 1;
    return x >> (s & mask) | x << ((-s) & mask);
}

// integral powers of 2
template<class T>
BOOST_CONSTEXPR bool has_single_bit( T x ) BOOST_NOEXCEPT
{
    return x != 0 && ( x & ( x - 1 ) ) == 0;
}

template<class T>
BOOST_CONSTEXPR T bit_width( T x ) BOOST_NOEXCEPT
{
    return std::numeric_limits<T>::digits - boost::core::countl_zero( x );
}

template<class T>
BOOST_CONSTEXPR T bit_ceil( T x ) BOOST_NOEXCEPT;

template<class T>
BOOST_CONSTEXPR T bit_floor( T x ) BOOST_NOEXCEPT
{
    return x == 0? 0: T(1) << ( boost::core::bit_width( x ) - 1 );
}

// endian

#if !defined(BOOST_NO_CXX11_SCOPED_ENUMS)

enum class endian
{
    little,
    big,
    // native = /* see description */
};

typedef endian endian_type;

#else

namespace endian
{

enum type
{
    little,
    big,
    // native = /* see description */
};

} // namespace endian

typedef endian::type endian_type;

#endif

} // namespace core
} // namespace boost

#endif  // #ifndef BOOST_CORE_BIT_HPP_INCLUDED
