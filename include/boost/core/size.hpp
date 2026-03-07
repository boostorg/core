/*
Copyright 2023 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_CORE_SIZE_HPP
#define BOOST_CORE_SIZE_HPP

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
BOOST_CORE_MODULE_EXPORT using std::size;
} /* boost */

#else // (defined(__cpp_lib_nonmember_container_access) ...

#include <boost/config/std/cstddef.hpp>

namespace boost {

template<class C>
BOOST_CORE_MODULE_EXPORT inline constexpr auto
size(const C& c) noexcept(noexcept(c.size())) -> decltype(c.size())
{
    return c.size();
}

template<class T, std::size_t N>
BOOST_CORE_MODULE_EXPORT inline constexpr std::size_t
size(T(&)[N]) noexcept
{
    return N;
}

} /* boost */

#endif // (defined(__cpp_lib_nonmember_container_access) ...

#endif

#endif
