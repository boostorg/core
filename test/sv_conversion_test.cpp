// Copyright 2021 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/core/detail/string_view.hpp>
#include <boost/core/lightweight_test.hpp>
#include <boost/config.hpp>

#if !defined(BOOST_NO_CXX17_HDR_MEMORY_RESOURCE)
# if defined(__apple_build_version__)
// Under macOS, it's possible for the header
// <memory_resource> to be present, but for
// libc++.dylib to not have support for it.
// https://github.com/boostorg/core/issues/162
#  define BOOST_NO_CXX17_HDR_MEMORY_RESOURCE
# endif
#endif

#include <string>
#if !defined(BOOST_NO_CXX17_HDR_STRING_VIEW)
# include <string_view>
#endif
#if !defined(BOOST_NO_CXX17_HDR_MEMORY_RESOURCE)
# include <memory_resource>
#endif

boost::core::string_view f( boost::core::string_view const& str )
{
    return str;
}

template<typename Char>
boost::core::basic_string_view<Char> f( boost::core::basic_string_view<Char> const& str )
{
    return str;
}

template<typename Char>
void subtest()
{
    std::basic_string<Char> s1( 3, Char('1') );
    s1[1] = Char('2');
    s1[2] = Char('3');

    std::basic_string<Char> s2 = f<Char>( s1 );
    BOOST_TEST( s1 == s2 );

#if ! (defined(BOOST_CLANG) && BOOST_CLANG_VERSION < 150000)
    // leads to undefined symbols in Clang < 15: https://github.com/llvm/llvm-project/issues/55560
    std::basic_string<Char> s3( (f<Char>( s1 )) );
    BOOST_TEST( s1 == s3 );
#endif
}

int main()
{
    {
        std::string s1( "123" );
        std::string s2 = f( s1 );

        BOOST_TEST_EQ( s1, s2 );
    }

#if !defined(BOOST_NO_CXX17_HDR_STRING_VIEW)

    {
        std::string_view s1( "123" );
        std::string_view s2 = f( s1 );

        BOOST_TEST_EQ( s1, s2 );
    }

#endif

#if !defined(BOOST_NO_CXX17_HDR_MEMORY_RESOURCE)

    {
        using pmr_string = std::basic_string<char, std::char_traits<char>, std::pmr::polymorphic_allocator<char>>;

        pmr_string s1( "123" );
        pmr_string s2 = f( s1 );

        BOOST_TEST_EQ( s1, s2 );
    }

#endif

#if !defined(BOOST_NO_CXX11_CHAR16_T)
    subtest<char16_t>();
#endif
#if !defined(BOOST_NO_CXX11_CHAR32_T)
    subtest<char32_t>();
#endif
#if defined(__cpp_char8_t) && __cpp_char8_t >= 201811L
    subtest<char8_t>();
#endif

    return boost::report_errors();
}
