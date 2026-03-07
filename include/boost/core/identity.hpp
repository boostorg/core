/*
Copyright 2021-2023 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_CORE_IDENTITY_HPP
#define BOOST_CORE_IDENTITY_HPP

#if defined(BOOST_USE_MODULES) && !defined(BOOST_CORE_INTERFACE_UNIT)
#ifndef BOOST_IN_MODULE_PURVIEW
import boost.core;
#endif
#else

#include <boost/core/detail/modules.hpp>
#include <boost/config.hpp>
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#include <boost/config/std/utility.hpp>
#endif

namespace boost {

BOOST_CORE_MODULE_EXPORT struct identity {
    typedef void is_transparent;

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    template<class T>
    BOOST_CONSTEXPR T&& operator()(T&& value) const BOOST_NOEXCEPT {
        return std::forward<T>(value);
    }
#else
    template<class T>
    BOOST_CONSTEXPR const T& operator()(const T& value) const BOOST_NOEXCEPT {
        return value;
    }

    template<class T>
    BOOST_CONSTEXPR T& operator()(T& value) const BOOST_NOEXCEPT {
        return value;
    }
#endif

    template<class>
    struct result { };

    template<class T>
    struct result<identity(T&)> {
        typedef T& type;
    };

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    template<class T>
    struct result<identity(T)> {
        typedef T&& type;
    };

    template<class T>
    struct result<identity(T&&)> {
        typedef T&& type;
    };
#endif
};

} /* boost */

#endif

#endif
