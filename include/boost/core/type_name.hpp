#ifndef BOOST_CORE_TYPE_NAME_HPP_INCLUDED
#define BOOST_CORE_TYPE_NAME_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

// std::string boost::core::type_name<T>()
//
// Copyright 2021 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/core/demangle.hpp>
#include <boost/config.hpp>
#include <string>
#include <functional>
#include <memory>
#include <utility>
#include <cstdio>
#include <cstddef>
#include <iosfwd>
#if !defined(BOOST_NO_CXX17_HDR_STRING_VIEW)
# include <string_view>
#endif

namespace boost
{
namespace core
{

namespace detail
{

// tn_identity

template<class T> struct tn_identity
{
    typedef T type;
};

// tn_enable_if

template<bool C, class T> struct tn_enable_if
{
};

template<class T> struct tn_enable_if<true, T>
{
    typedef T type;
};

// tn_is_reference

template<class T> struct tn_is_reference
{
    static const bool value = false;
};

template<class T> struct tn_is_reference<T&>
{
    static const bool value = true;
};

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

template<class T> struct tn_is_reference<T&&>
{
    static const bool value = true;
};

#endif

#if !defined(BOOST_NO_TYPEID)

// typeid_name

template<class T> std::string typeid_name()
{
    std::string r = boost::core::demangle( typeid(T).name() );

#if defined(_MSC_VER)

    if( r.substr( 0, 6 ) == "class " )
    {
        r = r.substr( 6 );
    }

    if( r.substr( 0, 7 ) == "struct " )
    {
        r = r.substr( 7 );
    }

    if( r.substr( 0, 5 ) == "enum " )
    {
        r = r.substr( 5 );
    }

#endif

    // libc++ inline namespace

    if( r.substr( 0, 10 ) == "std::__1::" )
    {
        r = "std::" + r.substr( 10 );
    }

    // libstdc++ inline namespace

    if( r.substr( 0, 14 ) == "std::__cxx11::" )
    {
        r = "std::" + r.substr( 14 );
    }

#if defined(BOOST_MSVC) && BOOST_MSVC == 1600

    // msvc-10.0 puts TR1 things in std::tr1

    if( r.substr( 0, 10 ) == "std::tr1::" )
    {
        r = "std::" + r.substr( 10 );
    }

#endif

    return r;
}

// template names

template<class T> std::string class_template_name()
{
    std::string r = typeid_name<T>();
    return r.substr( 0, r.find( '<' ) );
}

template<class T> std::string sequence_template_name()
{
    return class_template_name<T>();
}

template<class T> std::string set_template_name()
{
    return class_template_name<T>();
}

template<class T> std::string map_template_name()
{
    return class_template_name<T>();
}

template<class T> std::string array_template_name()
{
    return class_template_name<T>();
}

#else // #if !defined(BOOST_NO_TYPEID)

template<class T> std::string typeid_name()
{
    return "_Tp";
}

template<class T> std::string class_template_name()
{
    return "_Tm";
}

template<class T> std::string sequence_template_name()
{
    return "_Sq";
}

template<class T> std::string set_template_name()
{
    return "_St";
}

template<class T> std::string map_template_name()
{
    return "_Mp";
}

template<class T> std::string array_template_name()
{
    return "_Ar";
}

#endif

// tn_to_string

#if defined(BOOST_MSVC)
# pragma warning( push )
# pragma warning( disable: 4996 )
#endif

inline std::string tn_to_string( std::size_t n )
{
    char buffer[ 32 ];
    std::sprintf( buffer, "%lu", static_cast< unsigned long >( n ) );

    return buffer;
}

#if defined(BOOST_MSVC)
# pragma warning( pop )
#endif

// tn_add_each

#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

template<class T> int tn_add_each_impl( std::string& st )
{
    if( !st.empty() ) st += ", ";
    st += type_name( tn_identity<T>() );
    return 0;
};

template<class... T> std::string tn_add_each()
{
    std::string st;

    typedef int A[ sizeof...(T) + 1 ];
    (void)A{ 0, tn_add_each_impl<T>( st )... };

    return st;
};

#endif

// primary

template<class T> std::string type_name( tn_identity<T> )
{
    return typeid_name<T>();
}

// cv

#if !defined(BOOST_MSVC) || BOOST_MSVC >= 1900

template<class T> std::string type_name( tn_identity<T const> )
{
    return type_name( tn_identity<T>() ) + " const";
}

template<class T> std::string type_name( tn_identity<T volatile> )
{
    return type_name( tn_identity<T>() ) + " volatile";
}

template<class T> std::string type_name( tn_identity<T const volatile> )
{
    return type_name( tn_identity<T>() ) + " const volatile";
}

#else

template<class T>
typename tn_enable_if<!tn_is_reference<T>::value, std::string>::type
type_name( tn_identity<T const> )
{
    return type_name( tn_identity<T>() ) + " const";
}

template<class T>
typename tn_enable_if<!tn_is_reference<T>::value, std::string>::type
type_name( tn_identity<T volatile> )
{
    return type_name( tn_identity<T>() ) + " volatile";
}

template<class T>
typename tn_enable_if<!tn_is_reference<T>::value, std::string>::type
type_name( tn_identity<T const volatile> )
{
    return type_name( tn_identity<T>() ) + " const volatile";
}

#endif

// refs

#if !defined(BOOST_MSVC) || BOOST_MSVC >= 1900

template<class T> std::string type_name( tn_identity<T&> )
{
    return type_name( tn_identity<T>() ) + "&";
}

#else

template<class T>
typename tn_enable_if<!tn_is_reference<T>::value, std::string>::type
type_name( tn_identity<T&> )
{
    return type_name( tn_identity<T>() ) + "&";
}

#endif

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

template<class T> std::string type_name( tn_identity<T&&> )
{
    return type_name( tn_identity<T>() ) + "&&";
}

#endif

// function types

#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

template<class R, class... A> std::string type_name( tn_identity<R(A...)> )
{
    return type_name( tn_identity<R>() ) + '(' + tn_add_each<A...>() + ')';
}

#endif

// pointers

template<class T> std::string type_name( tn_identity<T*> )
{
    return type_name( tn_identity<T>() ) + "*";
}

#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

// function references

template<class R, class... A> std::string type_name( tn_identity<R(&)(A...)> )
{
    return type_name( tn_identity<R>() ) + "(&)(" + tn_add_each<A...>() + ')';
}

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

template<class R, class... A> std::string type_name( tn_identity<R(&&)(A...)> )
{
    return type_name( tn_identity<R>() ) + "(&&)(" + tn_add_each<A...>() + ')';
}

#endif

// function pointers

template<class R, class... A> std::string type_name( tn_identity<R(*)(A...)> )
{
    return type_name( tn_identity<R>() ) + "(*)(" + tn_add_each<A...>() + ')';
}

template<class R, class... A> std::string type_name( tn_identity<R(*&)(A...)> )
{
    return type_name( tn_identity<R>() ) + "(*&)(" + tn_add_each<A...>() + ')';
}

template<class R, class... A> std::string type_name( tn_identity<R(* const)(A...)> )
{
    return type_name( tn_identity<R>() ) + "(* const)(" + tn_add_each<A...>() + ')';
}

template<class R, class... A> std::string type_name( tn_identity<R(* const&)(A...)> )
{
    return type_name( tn_identity<R>() ) + "(* const&)(" + tn_add_each<A...>() + ')';
}

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

template<class R, class... A> std::string type_name( tn_identity<R(*&&)(A...)> )
{
    return type_name( tn_identity<R>() ) + "(*&&)(" + tn_add_each<A...>() + ')';
}

template<class R, class... A> std::string type_name( tn_identity<R(* const&&)(A...)> )
{
    return type_name( tn_identity<R>() ) + "(* const&&)(" + tn_add_each<A...>() + ')';
}

#endif

#endif

// arrays

template<class T> std::pair<std::string, std::string> array_prefix_suffix( tn_identity<T> )
{
    return std::pair<std::string, std::string>( type_name( tn_identity<T>() ), "" );
}

template<class T, std::size_t N> std::pair<std::string, std::string> array_prefix_suffix( tn_identity<T[N]> )
{
    std::pair<std::string, std::string> r = array_prefix_suffix( tn_identity<T>() );

    r.second = '[' + tn_to_string( N ) + ']' + r.second;

    return r;
}

template<class T> std::string array_type_name( tn_identity<T[]> )
{
    std::pair<std::string, std::string> r = array_prefix_suffix( tn_identity<T>() );
    return r.first + "[]" + r.second;
}

template<class T> std::string type_name( tn_identity<T[]> )
{
    return array_type_name( tn_identity<T[]>() );
}

template<class T> std::string type_name( tn_identity<T const[]> )
{
    return array_type_name( tn_identity<T const[]>() );
}

template<class T> std::string type_name( tn_identity<T volatile[]> )
{
    return array_type_name( tn_identity<T volatile[]>() );
}

template<class T> std::string type_name( tn_identity<T const volatile[]> )
{
    return array_type_name( tn_identity<T const volatile[]>() );
}

template<class T, std::size_t N> std::string array_type_name( tn_identity<T[N]> )
{
    std::pair<std::string, std::string> r = array_prefix_suffix( tn_identity<T[N]>() );
    return r.first + r.second;
}

template<class T, std::size_t N> std::string type_name( tn_identity<T[N]> )
{
    return array_type_name( tn_identity<T[N]>() );
}

template<class T, std::size_t N> std::string type_name( tn_identity<T const[N]> )
{
    return array_type_name( tn_identity<T const[N]>() );
}

template<class T, std::size_t N> std::string type_name( tn_identity<T volatile[N]> )
{
    return array_type_name( tn_identity<T volatile[N]>() );
}

template<class T, std::size_t N> std::string type_name( tn_identity<T const volatile[N]> )
{
    return array_type_name( tn_identity<T const volatile[N]>() );
}

// nullptr_t

#if !defined(BOOST_NO_CXX11_NULLPTR)

inline std::string type_name( tn_identity<std::nullptr_t> )
{
    return "std::nullptr_t";
}

#endif

// strings

template<template<class Ch, class Tr, class A> class L, class Ch> std::string type_name( tn_identity< L<Ch, std::char_traits<Ch>, std::allocator<Ch> > > )
{
    std::string tn = sequence_template_name< L<Ch, std::char_traits<Ch>, std::allocator<Ch> > >();
    return tn + '<' + type_name( tn_identity<Ch>() ) + '>';
}

inline std::string type_name( tn_identity<std::string> )
{
    return "std::string";
}

inline std::string type_name( tn_identity<std::wstring> )
{
    return "std::wstring";
}

#if !defined(BOOST_NO_CXX11_CHAR16_T)

inline std::string type_name( tn_identity<std::u16string> )
{
    return "std::u16string";
}

#endif

#if !defined(BOOST_NO_CXX11_CHAR32_T)

inline std::string type_name( tn_identity<std::u32string> )
{
    return "std::u32string";
}

#endif

#if defined(__cpp_char8_t) && __cpp_char8_t >= 201811L

inline std::string type_name( tn_identity<std::basic_string<char8_t>> )
{
    return "std::u8string";
}

#endif

// string views (et al)

template<template<class Ch, class Tr> class L, class Ch> std::string type_name( tn_identity< L<Ch, std::char_traits<Ch> > > )
{
    std::string tn = sequence_template_name< L<Ch, std::char_traits<Ch> > >();
    return tn + '<' + type_name( tn_identity<Ch>() ) + '>';
}

// needed for libstdc++
inline std::string type_name( tn_identity<std::ostream> )
{
    return "std::ostream";
}

#if !defined(BOOST_NO_CXX17_HDR_STRING_VIEW)

inline std::string type_name( tn_identity<std::string_view> )
{
    return "std::string_view";
}

inline std::string type_name( tn_identity<std::wstring_view> )
{
    return "std::wstring_view";
}

#if !defined(BOOST_NO_CXX11_CHAR16_T)

inline std::string type_name( tn_identity<std::u16string_view> )
{
    return "std::u16string_view";
}

#endif

#if !defined(BOOST_NO_CXX11_CHAR32_T)

inline std::string type_name( tn_identity<std::u32string_view> )
{
    return "std::u32string_view";
}

#endif

#if defined(__cpp_char8_t) && __cpp_char8_t >= 201811L

inline std::string type_name( tn_identity<std::basic_string_view<char8_t>> )
{
    return "std::u8string_view";
}

#endif

#endif

// class templates

#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

template<template<class...> class L, class... T> std::string type_name( tn_identity< L<T...> > )
{
    std::string tn = class_template_name< L<T...> >();
    std::string st = tn_add_each<T...>();

    return tn + '<' + st + '>';
}

#else

template<template<class T1> class L, class T1> std::string type_name( tn_identity< L<T1> > )
{
    std::string tn = class_template_name< L<T1> >();
    return tn + '<' + type_name( tn_identity<T1>() ) + '>';
}

template<template<class T1, class T2> class L, class T1, class T2> std::string type_name( tn_identity< L<T1, T2> > )
{
    std::string tn = class_template_name< L<T1, T2> >();
    return tn + '<' + type_name( tn_identity<T1>() ) + ", " + type_name( tn_identity<T2>() ) + '>';
}

#endif

// sequence containers

template<template<class T, class A> class L, class T> std::string type_name( tn_identity< L<T, std::allocator<T> > > )
{
    std::string tn = sequence_template_name< L<T, std::allocator<T> > >();
    return tn + '<' + type_name( tn_identity<T>() ) + '>';
}

// set

template<template<class T, class Pr, class A> class L, class T> std::string type_name( tn_identity< L<T, std::less<T>, std::allocator<T> > > )
{
    std::string tn = set_template_name< L<T, std::less<T>, std::allocator<T> > >();
    return tn + '<' + type_name( tn_identity<T>() ) + '>';
}

// map

template<template<class T, class U, class Pr, class A> class L, class T, class U> std::string type_name( tn_identity< L<T, U, std::less<T>, std::allocator<std::pair<T const, U> > > > )
{
    std::string tn = map_template_name< L<T, U, std::less<T>, std::allocator<std::pair<T const, U> > > >();
    return tn + '<' + type_name( tn_identity<T>() ) + ", " + type_name( tn_identity<U>() ) +  '>';
}

#if !defined(BOOST_NO_CXX11_HDR_FUNCTIONAL)

// unordered_set

template<template<class T, class H, class Eq, class A> class L, class T> std::string type_name( tn_identity< L<T, std::hash<T>, std::equal_to<T>, std::allocator<T> > > )
{
    std::string tn = set_template_name< L<T, std::hash<T>, std::equal_to<T>, std::allocator<T> > >();
    return tn + '<' + type_name( tn_identity<T>() ) + '>';
}

// unordered_map

template<template<class T, class U, class H, class Eq, class A> class L, class T, class U> std::string type_name( tn_identity< L<T, U, std::hash<T>, std::equal_to<T>, std::allocator<std::pair<T const, U> > > > )
{
    std::string tn = map_template_name< L<T, U, std::hash<T>, std::equal_to<T>, std::allocator<std::pair<T const, U> > > >();
    return tn + '<' + type_name( tn_identity<T>() ) + ", " + type_name( tn_identity<U>() ) +  '>';
}

#endif

// array

template<template<class T, std::size_t N> class L, class T, std::size_t N> std::string type_name( tn_identity< L<T, N> > )
{
    std::string tn = array_template_name< L<T, N> >();
    return tn + '<' + type_name( tn_identity<T>() ) + ", " + tn_to_string( N ) + '>';
}

} // namespace detail

template<class T> std::string type_name()
{
    return core::detail::type_name( core::detail::tn_identity<T>() );
}

} // namespace core
} // namespace boost

#endif  // #ifndef BOOST_CORE_TYPE_NAME_HPP_INCLUDED
