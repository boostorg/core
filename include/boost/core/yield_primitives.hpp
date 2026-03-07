// Make the header safe to include from libraries supporting modules
#if defined(BOOST_IN_MODULE_PURVIEW) && !defined(BOOST_CORE_YIELD_PRIMITIVES_HPP_INCLUDED)
#  error "Please #include <boost/core/yield_primitives.hpp> in your module global fragment"
#endif

#ifndef BOOST_CORE_YIELD_PRIMITIVES_HPP_INCLUDED
#define BOOST_CORE_YIELD_PRIMITIVES_HPP_INCLUDED

// Copyright 2023 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/core/detail/sp_thread_pause.hpp>
#include <boost/core/detail/sp_thread_yield.hpp>
#include <boost/core/detail/sp_thread_sleep.hpp>

#endif  // #ifndef BOOST_CORE_YIELD_PRIMITIVES_HPP_INCLUDED
