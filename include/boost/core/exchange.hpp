/*
Copyright 2018 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_CORE_EXCHANGE_HPP
#define BOOST_CORE_EXCHANGE_HPP

#include <boost/config.hpp>
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#include <utility>
#endif

namespace boost {

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
template<class T, class U = T>
BOOST_CXX14_CONSTEXPR inline T exchange(T& t, U&& u)
{
    T v = std::move(t);
    t = std::forward<U>(u);
    return v;
}
#else
namespace detail {

template<class T>
struct exchanger {
    typedef T type;
};

} /* detail */

template<class T>
inline T exchange(T& t, const typename detail::exchanger<T>::type& u)
{
    T v = t;
    t = u;
    return v;
}
#endif

} /* boost */

#endif
