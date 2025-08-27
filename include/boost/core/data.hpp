/*
Copyright 2023 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_CORE_DATA_HPP
#define BOOST_CORE_DATA_HPP

#include <initializer_list>
#include <cstddef>

#include <boost/core/detail/module_macro.hpp>

namespace boost {

BOOST_CORE_BEGIN_MODULE_EXPORT

template<class C>
inline constexpr auto
data(C& c) noexcept(noexcept(c.data())) -> decltype(c.data())
{
    return c.data();
}

template<class C>
inline constexpr auto
data(const C& c) noexcept(noexcept(c.data())) -> decltype(c.data())
{
    return c.data();
}

template<class T, std::size_t N>
inline constexpr T*
data(T(&a)[N]) noexcept
{
    return a;
}

template<class T>
inline constexpr const T*
data(std::initializer_list<T> l) noexcept
{
    return l.begin();
}

BOOST_CORE_END_MODULE_EXPORT

} /* boost */

#endif
