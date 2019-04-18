#ifndef BOOST_CORE_LIGHTWEIGHT_TEST_TRAIT_HPP
#define BOOST_CORE_LIGHTWEIGHT_TEST_TRAIT_HPP

// MS compatible compilers support #pragma once

#if defined(_MSC_VER)
# pragma once
#endif

// boost/core/lightweight_test_trait.hpp
//
// BOOST_TEST_TRAIT_TRUE, BOOST_TEST_TRAIT_FALSE, BOOST_TEST_TRAIT_SAME
//
// Copyright 2014 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/core/lightweight_test.hpp>
#include <boost/core/typeinfo.hpp>
#include <boost/core/is_same.hpp>

namespace boost
{

namespace detail
{

template< class T > inline void test_trait_impl( char const * trait, void (*)( T ),
  bool expected, char const * file, int line, char const * function )
{
    if( T::value == expected )
    {
        test_results();
    }
    else
    {
        BOOST_LIGHTWEIGHT_TEST_OSTREAM
            << file << "(" << line << "): predicate '" << trait << "' ["
            << boost::core::demangled_name( BOOST_CORE_TYPEID(T) ) << "]"
            << " test failed in function '" << function
            << "' (should have been " << ( expected? "true": "false" ) << ")"
            << std::endl;

        ++test_results().errors();
    }
}

template<class T> inline bool test_trait_same_impl_( T )
{
    return T::value;
}

template <class T>
struct test_trait_stream_type {
  static void stream() {
    BOOST_LIGHTWEIGHT_TEST_OSTREAM
      << boost::core::demangled_name( BOOST_CORE_TYPEID(T) );
  }
};

template <class T>
struct test_trait_stream_type<T const>  {
  static void stream() {
    test_trait_stream_type<T>::stream();
    BOOST_LIGHTWEIGHT_TEST_OSTREAM << " const"; }
};

template <class T>
struct test_trait_stream_type<T volatile> {
  static void stream() {
    test_trait_stream_type<T>::stream();
    BOOST_LIGHTWEIGHT_TEST_OSTREAM << " volatile"; }
};

template <class T>
struct test_trait_stream_type<T&>  {
  static void stream() {
    test_trait_stream_type<T>::stream();
    BOOST_LIGHTWEIGHT_TEST_OSTREAM << "&";
  }
};

template <class T>
struct test_trait_stream_type<T*>  {
  static void stream() {
    test_trait_stream_type<T>::stream();
    BOOST_LIGHTWEIGHT_TEST_OSTREAM << "*";
  }
};

template<class T1, class T2> inline void test_trait_same_impl( char const * types,
  boost::core::is_same<T1, T2> same, char const * file, int line, char const * function )
{
    if( test_trait_same_impl_( same ) )
    {
        test_results();
    }
    else
    {
        BOOST_LIGHTWEIGHT_TEST_OSTREAM
            << file << "(" << line << "): test 'is_same<" << types << ">'"
            << " failed in function '" << function
            << "' ('";

        test_trait_stream_type<T1>::stream();

        BOOST_LIGHTWEIGHT_TEST_OSTREAM << "' != '";

        test_trait_stream_type<T2>::stream();

        BOOST_LIGHTWEIGHT_TEST_OSTREAM << "')" << std::endl;

        ++test_results().errors();
    }
}

} // namespace detail

} // namespace boost

#define BOOST_TEST_TRAIT_TRUE(type) ( ::boost::detail::test_trait_impl(#type, (void(*)type)0, true, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION) )
#define BOOST_TEST_TRAIT_FALSE(type) ( ::boost::detail::test_trait_impl(#type, (void(*)type)0, false, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION) )
#define BOOST_TEST_TRAIT_SAME(...) ( ::boost::detail::test_trait_same_impl(#__VA_ARGS__, ::boost::core::is_same<__VA_ARGS__>(), __FILE__, __LINE__, BOOST_CURRENT_FUNCTION) )

#endif // #ifndef BOOST_CORE_LIGHTWEIGHT_TEST_TRAIT_HPP
