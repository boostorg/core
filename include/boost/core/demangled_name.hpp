#ifndef BOOST_CORE_DEMANGLED_NAME_HPP_INCLUDED
#define BOOST_CORE_DEMANGLED_NAME_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

// core::demangled_name( BOOST_CORE_TYPEID(T) )
//
// Copyright 2014 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/config.hpp>
#include <boost/core/typeinfo.hpp>
#include <string>

#if defined(__GLIBCXX__) || defined(__GLIBCPP__)
# include <cxxabi.h>
# include <cstdlib>
# include <cstddef>
# define BOOST_CORE_HAS_CXXABI_H
#endif

namespace boost
{

namespace core
{

namespace detail
{

#if defined( BOOST_CORE_HAS_CXXABI_H )

// lifted from boost/exception/detail/type_info.hpp

inline std::string demangle( char const * name )
{
    struct auto_free
    {
        explicit auto_free( char * ptr ): p( ptr )
        {
        }

        ~auto_free()
        {
            std::free( p );
        }

        char * p;
    };

    int status = 0;
    std::size_t size = 0;

    auto_free demangled( abi::__cxa_demangle( name, NULL, &size, &status ) );

    if( demangled.p )
    {
        return demangled.p;
    }
    else
    {
        return name;
    }
}

#else

inline std::string demangle( char const * name )
{
    return name;
}

#endif

} // namespace detail

inline std::string demangled_name( core::typeinfo const & ti )
{
#if defined( BOOST_NO_TYPEID )

    return ti.name();

#else

    return core::detail::demangle( ti.name() );

#endif
}

} // namespace core

} // namespace boost

#undef BOOST_CORE_HAS_CXXABI_H

#endif // #ifndef BOOST_CORE_DEMANGLED_NAME_HPP_INCLUDED
