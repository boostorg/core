#ifndef BOOST_CORE_SERIALIZATION_HPP_INCLUDED
#define BOOST_CORE_SERIALIZATION_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

// Copyright 2023 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt
//
// Utilities needed to implement serialization support
// without including a Boost.Serialization header

#include <boost/core/nvp.hpp>
#include <cstddef>

namespace boost
{

namespace serialization
{

// Forward declarations (needed for specializations)

template<class T> struct version;

// Our own version_type replacement. This has to be in
// the `serialization` namespace, because its only purpose
// is to add `serialization` as an associated namespace.

struct core_version_type
{
    unsigned int version_;

    core_version_type( unsigned int version ): version_( version ) {}
    operator unsigned int () const { return version_; }
};

} // namespace serialization

namespace core
{

// nvp

using serialization::nvp;
using serialization::make_nvp;

// split_free

namespace detail
{

template<bool IsSaving> struct load_or_save;

template<> struct load_or_save<true>
{
    template<class A, class T> void operator()( A& a, T& t, unsigned int v ) const
    {
		save( a, t, serialization::core_version_type( v ) );
    }
};

template<> struct load_or_save<false>
{
    template<class A, class T> void operator()( A& a, T& t, unsigned int v ) const
    {
        load( a, t, serialization::core_version_type( v ) );
    }
};

} // namespace detail

template<class A, class T> inline void split_free( A& a, T& t, unsigned int v )
{
    detail::load_or_save< A::is_saving::value >()( a, t, v );
}

} // namespace core
} // namespace boost

#endif  // #ifndef BOOST_CORE_SERIALIZATION_HPP_INCLUDED
