// Copyright 2021 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/core/type_name.hpp>
#include <boost/core/lightweight_test.hpp>
#include <boost/config.hpp>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <map>
#include <utility>
#include <cstddef>

#if !defined(BOOST_NO_CXX11_HDR_UNORDERED_SET)
# include <unordered_set>
#endif

#if !defined(BOOST_NO_CXX11_HDR_UNORDERED_MAP)
# include <unordered_map>
#endif

#if !defined(BOOST_NO_CXX11_HDR_ARRAY)
# include <array>
#endif

//

#define TEST(...) BOOST_TEST_EQ((boost::core::type_name<__VA_ARGS__>()), std::string(#__VA_ARGS__))

struct A
{
};

class B
{
};

template<class T1, class T2> struct X
{
};

int main()
{
    TEST(int);

    TEST(A);
    TEST(B);

    TEST(A const);
    TEST(A volatile);
    TEST(A const volatile);

    TEST(B&);
    TEST(B const&);

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    TEST(B&&);
    TEST(B const&&);

#endif

    TEST(void);
    TEST(void const);
    TEST(void volatile);
    TEST(void const volatile);

    TEST(A*);
    TEST(B const* volatile*);

    TEST(void*);
    TEST(void const* volatile*);

    TEST(A[]);
    TEST(A const[]);
    TEST(A volatile[]);
    TEST(A const volatile[]);

    TEST(B[1]);
    TEST(B const[1]);
    TEST(B volatile[1]);
    TEST(B const volatile[1]);

    TEST(A[][2][3]);
    TEST(A const[][2][3]);

    TEST(B[1][2][3]);
    TEST(B const volatile[1][2][3]);

#if !defined(BOOST_NO_CXX11_NULLPTR)

    TEST(std::nullptr_t);

#endif

    TEST(std::pair<A, B>);
    TEST(std::pair<A const*, B*> volatile&);

    TEST(std::string);
    TEST(std::wstring);

#if BOOST_CXX_VERSION >= 201100L

    TEST(std::u16string);
    TEST(std::u32string);

#endif

#if BOOST_CXX_VERSION >= 202000L

    TEST(std::u8string);

#endif

    TEST(X<A, B>);
    TEST(X<A const&, B&> volatile&);

    TEST(std::vector<int>);
    TEST(std::vector<A>);
    TEST(std::vector<std::string>);

    TEST(std::list<int>);
    TEST(std::list<B>);
    TEST(std::list<std::wstring>);

    TEST(std::deque<int>);
    TEST(std::deque<A>);
    TEST(std::deque<std::string>);

    TEST(std::set<int>);
    TEST(std::set<B>);
    TEST(std::set<std::string>);

    TEST(std::map<int, A>);
    TEST(std::map<std::string, B>);
    TEST(std::map<std::wstring, std::vector<std::string> const*> const&);

#if !defined(BOOST_NO_CXX11_HDR_UNORDERED_SET)

    TEST(std::unordered_set<int>);
    TEST(std::unordered_set<std::string>);

#endif

#if !defined(BOOST_NO_CXX11_HDR_UNORDERED_MAP)

    TEST(std::unordered_map<int, A>);
    TEST(std::unordered_map<std::string, B>);
    TEST(std::unordered_map<std::wstring, std::set<std::string>*>);

#endif

#if !defined(BOOST_NO_CXX11_HDR_ARRAY)

    TEST(std::array<std::string, 7>);
    TEST(std::array<std::wstring const*, 0> const&);

#endif
    return boost::report_errors();
}
