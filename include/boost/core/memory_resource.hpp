#ifndef BOOST_CORE_MEMORY_RESOURCE_HPP_INCLUDED
#define BOOST_CORE_MEMORY_RESOURCE_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//  Copyright 2023 Peter Dimov
//  Distributed under the Boost Software License, Version 1.0.
//  https://www.boost.org/LICENSE_1_0.txt

#if defined(BOOST_USE_MODULES) && !defined(BOOST_CORE_INTERFACE_UNIT)
#ifndef BOOST_IN_MODULE_PURVIEW
import boost.core;
#endif
#else

#include <boost/core/max_align.hpp>
#include <boost/config.hpp>
#include <boost/config/workaround.hpp>
#include <boost/config/std/cstddef.hpp>
#include <boost/core/detail/modules.hpp>

// Define our own placement new to avoid the inclusion of <new>
// (~9K extra lines) at Ion Gaztanhaga's request.
//
// We can use our own because [intro.object] p13 says:
//
// Any implicit or explicit invocation of a function named `operator new`
// or `operator new[]` implicitly creates objects in the returned region of
// storage and returns a pointer to a suitable created object.

namespace boost
{
namespace core
{
namespace detail
{

struct placement_new_tag {};

} // namespace detail
} // namespace core
} // namespace boost

inline void* operator new( std::size_t, void* p, boost::core::detail::placement_new_tag )
{
    return p;
}

inline void operator delete( void*, void*, boost::core::detail::placement_new_tag )
{
}

namespace boost
{
namespace core
{

BOOST_CORE_MODULE_EXPORT class memory_resource
{
public:

#if defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS) || BOOST_WORKAROUND(BOOST_GCC, < 40700)

    virtual ~memory_resource() {}

#else

    virtual ~memory_resource() = default;

#endif

    BOOST_ATTRIBUTE_NODISCARD inline void* allocate( std::size_t bytes, std::size_t alignment = max_align )
    {
        // https://github.com/boostorg/container/issues/199
        // https://cplusplus.github.io/LWG/issue3471

        return ::operator new( bytes, do_allocate( bytes, alignment ), core::detail::placement_new_tag() );
    }

    inline void deallocate( void* p, std::size_t bytes, std::size_t alignment = max_align )
    {
        do_deallocate( p, bytes, alignment );
    }

    inline bool is_equal( memory_resource const & other ) const BOOST_NOEXCEPT
    {
        return do_is_equal( other );
    }

private:

    virtual void* do_allocate( std::size_t bytes, std::size_t alignment ) = 0;
    virtual void do_deallocate( void* p, std::size_t bytes, std::size_t alignment ) = 0;

    virtual bool do_is_equal( memory_resource const & other ) const BOOST_NOEXCEPT = 0;
};

BOOST_CORE_MODULE_EXPORT inline bool operator==( memory_resource const& a, memory_resource const& b ) BOOST_NOEXCEPT
{
    return &a == &b || a.is_equal( b );
}

BOOST_CORE_MODULE_EXPORT inline bool operator!=( memory_resource const& a, memory_resource const& b ) BOOST_NOEXCEPT
{
    return !( a == b );
}

} // namespace core
} // namespace boost

#endif

#endif  // #ifndef BOOST_CORE_MEMORY_RESOURCE_HPP_INCLUDED
