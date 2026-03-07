#ifndef BOOST_CORE_DEMANGLE_HPP_INCLUDED
#define BOOST_CORE_DEMANGLE_HPP_INCLUDED

// core::demangle
//
// Copyright 2014 Peter Dimov
// Copyright 2014 Andrey Semashev
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#if defined(BOOST_USE_MODULES) && !defined(BOOST_CORE_INTERFACE_UNIT)

#ifndef BOOST_IN_MODULE_PURVIEW
import boost.core;
#endif

#else

#include <boost/config.hpp>
#include <boost/config/std/string.hpp>
#include <boost/core/detail/modules.hpp>

#if defined(BOOST_HAS_PRAGMA_ONCE)
# pragma once
#endif

#include <boost/core/detail/demangle_cxxabi.hpp>
#if defined( BOOST_CORE_HAS_CXXABI_H )
#  include <boost/config/std/cstdlib.hpp>
#  include <boost/config/std/cstddef.hpp>
#endif

namespace boost
{

namespace core
{

BOOST_CORE_MODULE_EXPORT inline char const * demangle_alloc( char const * name ) BOOST_NOEXCEPT;
BOOST_CORE_MODULE_EXPORT inline void demangle_free( char const * name ) BOOST_NOEXCEPT;

BOOST_CORE_MODULE_EXPORT class scoped_demangled_name
{
private:
    char const * m_p;

public:
    inline explicit scoped_demangled_name( char const * name ) BOOST_NOEXCEPT :
        m_p( demangle_alloc( name ) )
    {
    }

    inline ~scoped_demangled_name() BOOST_NOEXCEPT
    {
        demangle_free( m_p );
    }

    inline char const * get() const BOOST_NOEXCEPT
    {
        return m_p;
    }

    BOOST_DELETED_FUNCTION(scoped_demangled_name( scoped_demangled_name const& ))
    BOOST_DELETED_FUNCTION(scoped_demangled_name& operator= ( scoped_demangled_name const& ))
};


#if defined( BOOST_CORE_HAS_CXXABI_H )

BOOST_CORE_MODULE_EXPORT inline char const * demangle_alloc( char const * name ) BOOST_NOEXCEPT
{
    int status = 0;
    std::size_t size = 0;
    return abi::__cxa_demangle( name, NULL, &size, &status );
}

BOOST_CORE_MODULE_EXPORT inline void demangle_free( char const * name ) BOOST_NOEXCEPT
{
    std::free( const_cast< char* >( name ) );
}

BOOST_CORE_MODULE_EXPORT inline std::string demangle( char const * name )
{
    scoped_demangled_name demangled_name( name );
    char const * p = demangled_name.get();
    if( !p )
        p = name;
    return p;
}

#else

BOOST_CORE_MODULE_EXPORT inline char const * demangle_alloc( char const * name ) BOOST_NOEXCEPT
{
    return name;
}

BOOST_CORE_MODULE_EXPORT inline void demangle_free( char const * ) BOOST_NOEXCEPT
{
}

BOOST_CORE_MODULE_EXPORT inline std::string demangle( char const * name )
{
    return name;
}

#endif

} // namespace core

} // namespace boost

#undef BOOST_CORE_HAS_CXXABI_H

#endif

#endif // #ifndef BOOST_CORE_DEMANGLE_HPP_INCLUDED
