/*
Copyright 2023 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_CORE_DATA_HPP
#define BOOST_CORE_DATA_HPP

#if defined(BOOST_USE_MODULES) && !defined(BOOST_CORE_INTERFACE_UNIT)

#ifndef BOOST_IN_MODULE_PURVIEW
import boost.core;
#endif

#else

#include <boost/core/detail/modules.hpp>
#include <boost/config/std/iterator.hpp>

// Note: MSVC doesn't define __cpp_lib_nonmember_container_access but supports the feature even in C++14 mode
#if (defined(__cpp_lib_nonmember_container_access) && (__cpp_lib_nonmember_container_access >= 201411l)) || \
    (defined(_MSC_VER) && (_MSC_VER >= 1900))

namespace boost {
BOOST_CORE_MODULE_EXPORT using std::data;
} /* boost */

#else // (defined(__cpp_lib_nonmember_container_access) ...

#include <boost/config/std/cstddef.hpp>
#include <boost/config/std/initializer_list.hpp>

namespace boost {

template<class C>
BOOST_CORE_MODULE_EXPORT inline constexpr auto
data(C& c) noexcept(noexcept(c.data())) -> decltype(c.data())
{
    return c.data();
}

template<class C>
BOOST_CORE_MODULE_EXPORT inline constexpr auto
data(const C& c) noexcept(noexcept(c.data())) -> decltype(c.data())
{
    return c.data();
}

template<class T, std::size_t N>
BOOST_CORE_MODULE_EXPORT inline constexpr T*
data(T(&a)[N]) noexcept
{
    return a;
}

template<class T>
BOOST_CORE_MODULE_EXPORT inline constexpr const T*
data(std::initializer_list<T> l) noexcept
{
    return l.begin();
}

} /* boost */

#endif // (defined(__cpp_lib_nonmember_container_access) ...

#endif

#endif
