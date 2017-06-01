/*
Copyright Peter Dimov and David Abrahams 2002.

Copyright 2017 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_GET_POINTER_HPP
#define BOOST_GET_POINTER_HPP

#include <boost/config.hpp>
#include <boost/config/no_tr1/memory.hpp>

namespace boost {

template<class T>
inline T*
get_pointer(T* pointer) BOOST_NOEXCEPT
{
    return pointer;
}

#if !defined(BOOST_NO_CXX11_ALLOCATOR)
template<class T>
inline typename std::pointer_traits<T>::element_type*
get_pointer(const T& pointer) BOOST_NOEXCEPT
{
    return boost::get_pointer(pointer.operator->());
}
#else
template<class T>
inline typename T::element_type*
get_pointer(const T& pointer) BOOST_NOEXCEPT
{
    return pointer.get();
}
#endif

} /* boost */

#endif
