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

    return r;
}

// tn_to_string

#if defined(BOOST_MSVC)
# pragma warning( push )
# pragma warning( disable: 4996 )
#endif

inline std::string tn_to_string( unsigned long n )
{
    char buffer[ 32 ];
    std::sprintf( buffer, "%lu", n );

    return buffer;
}

#if defined(BOOST_MSVC)
# pragma warning( pop )
#endif

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

    using A = int[ sizeof...(T) + 1 ];
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

// refs

template<class T> std::string type_name( tn_identity<T&> )
{
    return type_name( tn_identity<T>() ) + "&";
}

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

    r.second = '[' + tn_to_string( static_cast<unsigned long>( N ) ) + ']' + r.second;

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

// class templates

#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

template<template<class...> class L, class... T> std::string type_name( tn_identity< L<T...> > )
{
    std::string tn = class_template_name< L<T...> >();
    std::string st = tn_add_each<T...>();

    return tn + '<' + st + '>';
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

} // namespace detail

template<class T> std::string type_name()
{
    return core::detail::type_name( core::detail::tn_identity<T>() );
}

} // namespace core
} // namespace boost

#endif  // #ifndef BOOST_CORE_TYPE_NAME_HPP_INCLUDED
