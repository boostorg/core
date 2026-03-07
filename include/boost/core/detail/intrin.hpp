// Module-aware wrapper for <intrin.h>
// Ensures that we don't accidentally pour names into Boost.Core's module purview
#if defined(BOOST_IN_MODULE_PURVIEW) && !defined(BOOST_CORE_INTRIN_INCLUDED)
#  error "Please #include <boost/core/detail/intrin.hpp> in your module global fragment"
#endif

#ifndef BOOST_CORE_INTRIN_INCLUDED
#define BOOST_CORE_INTRIN_INCLUDED
#include <intrin.h>
#endif
