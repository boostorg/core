// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CORE_IGNORE_UNUSED_HPP
#define BOOST_CORE_IGNORE_UNUSED_HPP

#if defined(BOOST_USE_MODULES) && !defined(BOOST_CORE_INTERFACE_UNIT)

#ifndef BOOST_IN_MODULE_PURVIEW
import boost.core;
#endif

#else

#include <boost/core/detail/modules.hpp>
#include <boost/config.hpp>

namespace boost {

#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

BOOST_CORE_MODULE_EXPORT template <typename... Ts>
BOOST_FORCEINLINE BOOST_CXX14_CONSTEXPR void ignore_unused(Ts&& ...)
{}

#else

BOOST_CORE_MODULE_EXPORT template <typename... Ts>
BOOST_FORCEINLINE BOOST_CXX14_CONSTEXPR void ignore_unused(Ts const& ...)
{}

#endif

BOOST_CORE_MODULE_EXPORT template <typename... Ts>
BOOST_FORCEINLINE BOOST_CXX14_CONSTEXPR void ignore_unused()
{}

#else // !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

BOOST_CORE_MODULE_EXPORT template <typename T1>
BOOST_FORCEINLINE BOOST_CXX14_CONSTEXPR void ignore_unused(T1&)
{}

BOOST_CORE_MODULE_EXPORT template <typename T1>
BOOST_FORCEINLINE BOOST_CXX14_CONSTEXPR void ignore_unused(T1 const&)
{}

BOOST_CORE_MODULE_EXPORT template <typename T1, typename T2>
BOOST_FORCEINLINE BOOST_CXX14_CONSTEXPR void ignore_unused(T1&, T2&)
{}

BOOST_CORE_MODULE_EXPORT template <typename T1, typename T2>
BOOST_FORCEINLINE BOOST_CXX14_CONSTEXPR void ignore_unused(T1 const&, T2 const&)
{}

BOOST_CORE_MODULE_EXPORT template <typename T1, typename T2, typename T3>
BOOST_FORCEINLINE BOOST_CXX14_CONSTEXPR void ignore_unused(T1&, T2&, T3&)
{}

BOOST_CORE_MODULE_EXPORT template <typename T1, typename T2, typename T3>
BOOST_FORCEINLINE BOOST_CXX14_CONSTEXPR void ignore_unused(T1 const&, T2 const&, T3 const&)
{}

BOOST_CORE_MODULE_EXPORT template <typename T1, typename T2, typename T3, typename T4>
BOOST_FORCEINLINE BOOST_CXX14_CONSTEXPR void ignore_unused(T1&, T2&, T3&, T4&)
{}

BOOST_CORE_MODULE_EXPORT template <typename T1, typename T2, typename T3, typename T4>
BOOST_FORCEINLINE BOOST_CXX14_CONSTEXPR void ignore_unused(T1 const&, T2 const&, T3 const&, T4 const&)
{}

BOOST_CORE_MODULE_EXPORT template <typename T1, typename T2, typename T3, typename T4, typename T5>
BOOST_FORCEINLINE BOOST_CXX14_CONSTEXPR void ignore_unused(T1&, T2&, T3&, T4&, T5&)
{}

BOOST_CORE_MODULE_EXPORT template <typename T1, typename T2, typename T3, typename T4, typename T5>
BOOST_FORCEINLINE BOOST_CXX14_CONSTEXPR void ignore_unused(T1 const&, T2 const&, T3 const&, T4 const&, T5 const&)
{}

BOOST_CORE_MODULE_EXPORT template <typename T1>
BOOST_FORCEINLINE BOOST_CXX14_CONSTEXPR void ignore_unused()
{}

BOOST_CORE_MODULE_EXPORT template <typename T1, typename T2>
BOOST_FORCEINLINE BOOST_CXX14_CONSTEXPR void ignore_unused()
{}

BOOST_CORE_MODULE_EXPORT template <typename T1, typename T2, typename T3>
BOOST_FORCEINLINE BOOST_CXX14_CONSTEXPR void ignore_unused()
{}

BOOST_CORE_MODULE_EXPORT template <typename T1, typename T2, typename T3, typename T4>
BOOST_FORCEINLINE BOOST_CXX14_CONSTEXPR void ignore_unused()
{}

BOOST_CORE_MODULE_EXPORT template <typename T1, typename T2, typename T3, typename T4, typename T5>
BOOST_FORCEINLINE BOOST_CXX14_CONSTEXPR void ignore_unused()
{}

#endif

} // namespace boost

#endif

#endif // BOOST_CORE_IGNORE_UNUSED_HPP
