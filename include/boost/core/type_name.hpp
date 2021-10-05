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
#include <boost/core/is_same.hpp>
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

// tn_remove_const

template<class T> struct tn_remove_const
{
    typedef T type;
};

template<class T> struct tn_remove_const<T const>
{
    typedef T type;
};

// tn_is_function (also catches references but that's OK)

#if defined(BOOST_MSVC)
# pragma warning(push)
# pragma warning(disable: 4180 4181)
#endif

template<class T, class U = typename tn_remove_const<T>::type> struct tn_is_function: core::is_same<U, U const>
{
};

#if defined(BOOST_MSVC)
# pragma warning(pop)
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
    st += type_name( tn_identity<T>(), "" );
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

template<class T> std::string type_name( tn_identity<T>, std::string const& suffix )
{
    return typeid_name<T>() + suffix;
}

// cv

#if !defined(BOOST_MSVC) || BOOST_MSVC >= 1900

template<class T> std::string type_name( tn_identity<T const>, std::string const& suffix )
{
    return type_name( tn_identity<T>(), " const" + suffix );
}

template<class T> std::string type_name( tn_identity<T volatile>, std::string const& suffix )
{
    return type_name( tn_identity<T>(), " volatile" + suffix );
}

template<class T> std::string type_name( tn_identity<T const volatile>, std::string const& suffix )
{
    return type_name( tn_identity<T>(), " const volatile" + suffix );
}

#else

template<class T>
typename tn_enable_if<!tn_is_function<T>::value, std::string>::type
type_name( tn_identity<T const>, std::string const& suffix )
{
    return type_name( tn_identity<T>(), " const" + suffix );
}

template<class T>
typename tn_enable_if<!tn_is_function<T>::value, std::string>::type
type_name( tn_identity<T volatile>, std::string const& suffix )
{
    return type_name( tn_identity<T>(), " volatile" + suffix );
}

template<class T>
typename tn_enable_if<!tn_is_function<T>::value, std::string>::type
type_name( tn_identity<T const volatile>, std::string const& suffix )
{
    return type_name( tn_identity<T>(), " const volatile" + suffix );
}

#endif

// refs

#if !defined(BOOST_MSVC) || BOOST_MSVC >= 1900

template<class T> std::string type_name( tn_identity<T&>, std::string const& suffix )
{
    return type_name( tn_identity<T>(), "&" + suffix );
}

#else

template<class T>
typename tn_enable_if<!tn_is_reference<T>::value, std::string>::type
type_name( tn_identity<T&>, std::string const& suffix )
{
    return type_name( tn_identity<T>(), "&" + suffix );
}

#endif

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

template<class T> std::string type_name( tn_identity<T&&>, std::string const& suffix )
{
    return type_name( tn_identity<T>(), "&&" + suffix );
}

#endif

// function types

#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

template<class R, class... A> std::string function_type_name( tn_identity<R(A...)>, std::string const& trailer, std::string const& suffix )
{
    std::string r = type_name( tn_identity<R>(), "" );

    if( !suffix.empty() )
    {
        r += '(';

        if( suffix.front() == ' ' )
        {
            r += suffix.substr( 1 );
        }
        else
        {
            r += suffix;
        }

        r += ')';
    }

    r += '(' + tn_add_each<A...>() + ')';
    r += trailer;

    return r;
}

template<class R, class... A> std::string type_name( tn_identity<R(A...)>, std::string const& suffix )
{
    return function_type_name( tn_identity<R(A...)>(), "", suffix );
}

template<class R, class... A> std::string type_name( tn_identity<R(A...) const>, std::string const& suffix )
{
    return function_type_name( tn_identity<R(A...)>(), " const", suffix );
}

template<class R, class... A> std::string type_name( tn_identity<R(A...) volatile>, std::string const& suffix )
{
    return function_type_name( tn_identity<R(A...)>(), " volatile", suffix );
}

template<class R, class... A> std::string type_name( tn_identity<R(A...) const volatile>, std::string const& suffix )
{
    return function_type_name( tn_identity<R(A...)>(), " const volatile", suffix );
}

#if !defined(BOOST_NO_CXX11_REF_QUALIFIERS)

template<class R, class... A> std::string type_name( tn_identity<R(A...) &>, std::string const& suffix )
{
    return function_type_name( tn_identity<R(A...)>(), " &", suffix );
}

template<class R, class... A> std::string type_name( tn_identity<R(A...) const &>, std::string const& suffix )
{
    return function_type_name( tn_identity<R(A...)>(), " const &", suffix );
}

template<class R, class... A> std::string type_name( tn_identity<R(A...) volatile &>, std::string const& suffix )
{
    return function_type_name( tn_identity<R(A...)>(), " volatile &", suffix );
}

template<class R, class... A> std::string type_name( tn_identity<R(A...) const volatile &>, std::string const& suffix )
{
    return function_type_name( tn_identity<R(A...)>(), " const volatile &", suffix );
}

template<class R, class... A> std::string type_name( tn_identity<R(A...) &&>, std::string const& suffix )
{
    return function_type_name( tn_identity<R(A...)>(), " &&", suffix );
}

template<class R, class... A> std::string type_name( tn_identity<R(A...) const &&>, std::string const& suffix )
{
    return function_type_name( tn_identity<R(A...)>(), " const &&", suffix );
}

template<class R, class... A> std::string type_name( tn_identity<R(A...) volatile &&>, std::string const& suffix )
{
    return function_type_name( tn_identity<R(A...)>(), " volatile &&", suffix );
}

template<class R, class... A> std::string type_name( tn_identity<R(A...) const volatile &&>, std::string const& suffix )
{
    return function_type_name( tn_identity<R(A...)>(), " const volatile &&", suffix );
}

#endif

#if defined( __cpp_noexcept_function_type ) || defined( _NOEXCEPT_TYPES_SUPPORTED )

template<class R, class... A> std::string type_name( tn_identity<R(A...) noexcept>, std::string const& suffix )
{
    return function_type_name( tn_identity<R(A...)>(), " noexcept", suffix );
}

template<class R, class... A> std::string type_name( tn_identity<R(A...) const noexcept>, std::string const& suffix )
{
    return function_type_name( tn_identity<R(A...)>(), " const noexcept", suffix );
}

template<class R, class... A> std::string type_name( tn_identity<R(A...) volatile noexcept>, std::string const& suffix )
{
    return function_type_name( tn_identity<R(A...)>(), " volatile noexcept", suffix );
}

template<class R, class... A> std::string type_name( tn_identity<R(A...) const volatile noexcept>, std::string const& suffix )
{
    return function_type_name( tn_identity<R(A...)>(), " const volatile noexcept", suffix );
}

template<class R, class... A> std::string type_name( tn_identity<R(A...) & noexcept>, std::string const& suffix )
{
    return function_type_name( tn_identity<R(A...)>(), " & noexcept", suffix );
}

template<class R, class... A> std::string type_name( tn_identity<R(A...) const & noexcept>, std::string const& suffix )
{
    return function_type_name( tn_identity<R(A...)>(), " const & noexcept", suffix );
}

template<class R, class... A> std::string type_name( tn_identity<R(A...) volatile & noexcept>, std::string const& suffix )
{
    return function_type_name( tn_identity<R(A...)>(), " volatile & noexcept", suffix );
}

template<class R, class... A> std::string type_name( tn_identity<R(A...) const volatile & noexcept>, std::string const& suffix )
{
    return function_type_name( tn_identity<R(A...)>(), " const volatile & noexcept", suffix );
}

template<class R, class... A> std::string type_name( tn_identity<R(A...) && noexcept>, std::string const& suffix )
{
    return function_type_name( tn_identity<R(A...)>(), " && noexcept", suffix );
}

template<class R, class... A> std::string type_name( tn_identity<R(A...) const && noexcept>, std::string const& suffix )
{
    return function_type_name( tn_identity<R(A...)>(), " const && noexcept", suffix );
}

template<class R, class... A> std::string type_name( tn_identity<R(A...) volatile && noexcept>, std::string const& suffix )
{
    return function_type_name( tn_identity<R(A...)>(), " volatile && noexcept", suffix );
}

template<class R, class... A> std::string type_name( tn_identity<R(A...) const volatile && noexcept>, std::string const& suffix )
{
    return function_type_name( tn_identity<R(A...)>(), " const volatile && noexcept", suffix );
}

#endif

#endif // #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

// pointers

template<class T> std::string type_name( tn_identity<T*>, std::string const& suffix )
{
    return type_name( tn_identity<T>(), "*" + suffix );
}

// arrays

template<class T> std::pair<std::string, std::string> array_prefix_suffix( tn_identity<T> )
{
    return std::pair<std::string, std::string>( type_name( tn_identity<T>(), "" ), "" );
}

template<class T, std::size_t N> std::pair<std::string, std::string> array_prefix_suffix( tn_identity<T[N]> )
{
    std::pair<std::string, std::string> r = array_prefix_suffix( tn_identity<T>() );

    r.second = '[' + tn_to_string( N ) + ']' + r.second;

    return r;
}

template<class T> std::string array_type_name( tn_identity<T[]>, std::string const& suffix )
{
    std::pair<std::string, std::string> r = array_prefix_suffix( tn_identity<T>() );

    if( suffix.empty() )
    {
        return r.first + "[]" + r.second;
    }
    else
    {
        return r.first + '(' + suffix + ")[]" + r.second;
    }
}

template<class T> std::string type_name( tn_identity<T[]>, std::string const& suffix )
{
    return array_type_name( tn_identity<T[]>(), suffix );
}

template<class T> std::string type_name( tn_identity<T const[]>, std::string const& suffix )
{
    return array_type_name( tn_identity<T const[]>(), suffix );
}

template<class T> std::string type_name( tn_identity<T volatile[]>, std::string const& suffix )
{
    return array_type_name( tn_identity<T volatile[]>(), suffix );
}

template<class T> std::string type_name( tn_identity<T const volatile[]>, std::string const& suffix )
{
    return array_type_name( tn_identity<T const volatile[]>(), suffix );
}

template<class T, std::size_t N> std::string array_type_name( tn_identity<T[N]>, std::string const& suffix )
{
    std::pair<std::string, std::string> r = array_prefix_suffix( tn_identity<T[N]>() );

    if( suffix.empty() )
    {
        return r.first + r.second;
    }
    else
    {
        return r.first + '(' + suffix + ")" + r.second;
    }
}

template<class T, std::size_t N> std::string type_name( tn_identity<T[N]>, std::string const& suffix )
{
    return array_type_name( tn_identity<T[N]>(), suffix );
}

template<class T, std::size_t N> std::string type_name( tn_identity<T const[N]>, std::string const& suffix )
{
    return array_type_name( tn_identity<T const[N]>(), suffix );
}

template<class T, std::size_t N> std::string type_name( tn_identity<T volatile[N]>, std::string const& suffix )
{
    return array_type_name( tn_identity<T volatile[N]>(), suffix );
}

template<class T, std::size_t N> std::string type_name( tn_identity<T const volatile[N]>, std::string const& suffix )
{
    return array_type_name( tn_identity<T const volatile[N]>(), suffix );
}

// pointers to members

template<class R, class T> std::string type_name( tn_identity<R T::*>, std::string const& suffix )
{
    return type_name( tn_identity<R>(), ' ' + type_name( tn_identity<T>(), "" ) + "::*" + suffix );
}

// nullptr_t

#if !defined(BOOST_NO_CXX11_NULLPTR)

inline std::string type_name( tn_identity<std::nullptr_t>, std::string const& suffix )
{
    return "std::nullptr_t" + suffix;
}

#endif

// strings

template<template<class Ch, class Tr, class A> class L, class Ch> std::string type_name( tn_identity< L<Ch, std::char_traits<Ch>, std::allocator<Ch> > >, std::string const& suffix )
{
    std::string tn = sequence_template_name< L<Ch, std::char_traits<Ch>, std::allocator<Ch> > >();
    return tn + '<' + type_name( tn_identity<Ch>(), "" ) + '>' + suffix;
}

inline std::string type_name( tn_identity<std::string>, std::string const& suffix )
{
    return "std::string" + suffix;
}

inline std::string type_name( tn_identity<std::wstring>, std::string const& suffix )
{
    return "std::wstring" + suffix;
}

#if !defined(BOOST_NO_CXX11_CHAR16_T)

inline std::string type_name( tn_identity<std::u16string>, std::string const& suffix )
{
    return "std::u16string" + suffix;
}

#endif

#if !defined(BOOST_NO_CXX11_CHAR32_T)

inline std::string type_name( tn_identity<std::u32string>, std::string const& suffix )
{
    return "std::u32string" + suffix;
}

#endif

#if defined(__cpp_char8_t) && __cpp_char8_t >= 201811L

inline std::string type_name( tn_identity<std::basic_string<char8_t>>, std::string const& suffix )
{
    return "std::u8string" + suffix;
}

#endif

// string views (et al)

template<template<class Ch, class Tr> class L, class Ch> std::string type_name( tn_identity< L<Ch, std::char_traits<Ch> > >, std::string const& suffix )
{
    std::string tn = sequence_template_name< L<Ch, std::char_traits<Ch> > >();
    return tn + '<' + type_name( tn_identity<Ch>(), "" ) + '>' + suffix;
}

// needed for libstdc++
inline std::string type_name( tn_identity<std::ostream>, std::string const& suffix )
{
    return "std::ostream" + suffix;
}

#if !defined(BOOST_NO_CXX17_HDR_STRING_VIEW)

inline std::string type_name( tn_identity<std::string_view>, std::string const& suffix )
{
    return "std::string_view" + suffix;
}

inline std::string type_name( tn_identity<std::wstring_view>, std::string const& suffix )
{
    return "std::wstring_view" + suffix;
}

#if !defined(BOOST_NO_CXX11_CHAR16_T)

inline std::string type_name( tn_identity<std::u16string_view>, std::string const& suffix )
{
    return "std::u16string_view" + suffix;
}

#endif

#if !defined(BOOST_NO_CXX11_CHAR32_T)

inline std::string type_name( tn_identity<std::u32string_view>, std::string const& suffix )
{
    return "std::u32string_view" + suffix;
}

#endif

#if defined(__cpp_char8_t) && __cpp_char8_t >= 201811L

inline std::string type_name( tn_identity<std::basic_string_view<char8_t>>, std::string const& suffix )
{
    return "std::u8string_view" + suffix;
}

#endif

#endif

// class templates

#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

template<template<class...> class L, class... T> std::string type_name( tn_identity< L<T...> >, std::string const& suffix )
{
    std::string tn = class_template_name< L<T...> >();
    std::string st = tn_add_each<T...>();

    return tn + '<' + st + '>' + suffix;
}

#else

template<template<class T1> class L, class T1> std::string type_name( tn_identity< L<T1> >, std::string const& suffix )
{
    std::string tn = class_template_name< L<T1> >();
    return tn + '<' + type_name( tn_identity<T1>(), "" ) + '>' + suffix;
}

template<template<class T1, class T2> class L, class T1, class T2> std::string type_name( tn_identity< L<T1, T2> >, std::string const& suffix )
{
    std::string tn = class_template_name< L<T1, T2> >();
    return tn + '<' + type_name( tn_identity<T1>(), "" ) + ", " + type_name( tn_identity<T2>(), "" ) + '>' + suffix;
}

#endif

// sequence containers

template<template<class T, class A> class L, class T> std::string type_name( tn_identity< L<T, std::allocator<T> > >, std::string const& suffix )
{
    std::string tn = sequence_template_name< L<T, std::allocator<T> > >();
    return tn + '<' + type_name( tn_identity<T>(), "" ) + '>' + suffix;
}

// set

template<template<class T, class Pr, class A> class L, class T> std::string type_name( tn_identity< L<T, std::less<T>, std::allocator<T> > >, std::string const& suffix )
{
    std::string tn = set_template_name< L<T, std::less<T>, std::allocator<T> > >();
    return tn + '<' + type_name( tn_identity<T>(), "" ) + '>' + suffix;
}

// map

template<template<class T, class U, class Pr, class A> class L, class T, class U> std::string type_name( tn_identity< L<T, U, std::less<T>, std::allocator<std::pair<T const, U> > > >, std::string const& suffix )
{
    std::string tn = map_template_name< L<T, U, std::less<T>, std::allocator<std::pair<T const, U> > > >();
    return tn + '<' + type_name( tn_identity<T>(), "" ) + ", " + type_name( tn_identity<U>(), "" ) +  '>' + suffix;
}

#if !defined(BOOST_NO_CXX11_HDR_FUNCTIONAL)

// unordered_set

template<template<class T, class H, class Eq, class A> class L, class T> std::string type_name( tn_identity< L<T, std::hash<T>, std::equal_to<T>, std::allocator<T> > >, std::string const& suffix )
{
    std::string tn = set_template_name< L<T, std::hash<T>, std::equal_to<T>, std::allocator<T> > >();
    return tn + '<' + type_name( tn_identity<T>(), "" ) + '>' + suffix;
}

// unordered_map

template<template<class T, class U, class H, class Eq, class A> class L, class T, class U> std::string type_name( tn_identity< L<T, U, std::hash<T>, std::equal_to<T>, std::allocator<std::pair<T const, U> > > >, std::string const& suffix )
{
    std::string tn = map_template_name< L<T, U, std::hash<T>, std::equal_to<T>, std::allocator<std::pair<T const, U> > > >();
    return tn + '<' + type_name( tn_identity<T>(), "" ) + ", " + type_name( tn_identity<U>(), "" ) +  '>' + suffix;
}

#endif

// array

template<template<class T, std::size_t N> class L, class T, std::size_t N> std::string type_name( tn_identity< L<T, N> >, std::string const& suffix )
{
    std::string tn = array_template_name< L<T, N> >();
    return tn + '<' + type_name( tn_identity<T>(), "" ) + ", " + tn_to_string( N ) + '>' + suffix;
}

} // namespace detail

template<class T> std::string type_name()
{
    return core::detail::type_name( core::detail::tn_identity<T>(), "" );
}

} // namespace core
} // namespace boost

#endif  // #ifndef BOOST_CORE_TYPE_NAME_HPP_INCLUDED
