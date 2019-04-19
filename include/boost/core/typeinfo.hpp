#ifndef BOOST_CORE_TYPEINFO_HPP_INCLUDED
#define BOOST_CORE_TYPEINFO_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//  core::typeinfo, BOOST_CORE_TYPEID
//
//  Copyright 2007, 2014 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <boost/config.hpp>

#if defined( BOOST_NO_TYPEID )

#include <boost/current_function.hpp>
#include <functional>
#include <cstring>

namespace boost
{

namespace core
{

class typeinfo
{
private:

    typeinfo( typeinfo const& );
    typeinfo& operator=( typeinfo const& );

    char const * name_;
    void (*lib_id_)();

public:

    typeinfo( char const * name, void (*lib_id)() ): name_( name ), lib_id_( lib_id )
    {
    }

    bool operator==( typeinfo const& rhs ) const
    {
#if ( defined(_WIN32) || defined(__CYGWIN__) ) && defined(__GNUC__) && !defined(BOOST_DISABLE_CURRENT_FUNCTION)

        return lib_id_ == rhs.lib_id_? this == &rhs: std::strcmp( name_, rhs.name_ ) == 0;

#else

        return this == &rhs;

#endif
    }

    bool operator!=( typeinfo const& rhs ) const
    {
        return !( *this == rhs );
    }

    bool before( typeinfo const& rhs ) const
    {
#if ( defined(_WIN32) || defined(__CYGWIN__) ) && defined(__GNUC__) && !defined(BOOST_DISABLE_CURRENT_FUNCTION)

        return lib_id_ == rhs.lib_id_? std::less< typeinfo const* >()( this, &rhs ): std::strcmp( name_, rhs.name_ ) < 0;

#else

        return std::less< typeinfo const* >()( this, &rhs );

#endif
    }

    char const* name() const
    {
        return name_;
    }
};

inline char const * demangled_name( core::typeinfo const & ti )
{
    return ti.name();
}

} // namespace core

namespace detail
{

template<class T> struct BOOST_SYMBOL_VISIBLE core_typeid_
{
    static boost::core::typeinfo ti_;

    static char const * name()
    {
        return BOOST_CURRENT_FUNCTION;
    }
};

BOOST_SYMBOL_VISIBLE inline void core_typeid_lib_id()
{
}

template<class T> boost::core::typeinfo core_typeid_< T >::ti_( core_typeid_< T >::name(), &core_typeid_lib_id );

template<class T> struct core_typeid_< T & >: core_typeid_< T >
{
};

template<class T> struct core_typeid_< T const >: core_typeid_< T >
{
};

template<class T> struct core_typeid_< T volatile >: core_typeid_< T >
{
};

template<class T> struct core_typeid_< T const volatile >: core_typeid_< T >
{
};

} // namespace detail

} // namespace boost

#define BOOST_CORE_TYPEID(T) (boost::detail::core_typeid_<T>::ti_)

#else

#include <boost/core/demangle.hpp>
#include <boost/type.hpp>
#include <typeinfo>
#include <string>

namespace boost
{

namespace detail
{

std::string unwrap_type_name(const std::string& demangled_name) {
    // Find first occurence of "type" from boost::type.
    std::string::size_type begin = demangled_name.find("type");
    if (begin == std::string::npos) {
        // Couldn't find "type" string. Return source string.
        return demangled_name;
    }
    // skip one leading "<" and any space characters
    begin = demangled_name.find('<', begin);
    if (begin == std::string::npos)
        return demangled_name;
    ++begin;
    while (begin != demangled_name.size() && demangled_name[begin] == ' ') ++begin;
    // remove trailing ">" and any space characters
    std::string::size_type last = demangled_name.rfind('>');
    if (last == std::string::npos)
        return demangled_name;
    --last;
    while (last != begin && demangled_name[last] == ' ') --last;
    return demangled_name.substr(begin, last - begin + 1);
}

} // namespace detail

namespace core
{

#if defined( BOOST_NO_STD_TYPEINFO )

typedef ::type_info typeinfo;

#else

typedef std::type_info typeinfo;

#endif

inline std::string demangled_name( core::typeinfo const & ti )
{
    return boost::detail::unwrap_type_name(core::demangle( ti.name() ));
}

} // namespace core

} // namespace boost


#define BOOST_CORE_TYPEID(T) typeid(boost::type<T>)

#endif

#endif  // #ifndef BOOST_CORE_TYPEINFO_HPP_INCLUDED
