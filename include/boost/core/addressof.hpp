/*
Copyright (C) 2002 Brad King (brad.king@kitware.com)
                   Douglas Gregor (gregod@cs.rpi.edu)

Copyright (C) 2002, 2008, 2013 Peter Dimov

Copyright (C) 2017 Glen Joseph Fernandes (glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0. (See
accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef BOOST_CORE_ADDRESSOF_HPP
#define BOOST_CORE_ADDRESSOF_HPP

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <cstddef>

#if defined(BOOST_NO_SFINAE_EXPR) || \
    defined(BOOST_NO_CXX11_RVALUE_REFERENCES) || \
    defined(BOOST_NO_CXX11_CONSTEXPR) || \
    defined(BOOST_NO_CXX11_DECLTYPE) || \
    (defined(BOOST_MSVC) && \
        BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1900)))
#define BOOST_CORE_NO_CONSTEXPR_ADDRESSOF
#endif

namespace boost {
namespace core {
namespace detail {

template<class T>
class addressof_ref {
public:
    BOOST_FORCEINLINE addressof_ref(T& o) BOOST_NOEXCEPT
        : o_(o) { }
    BOOST_FORCEINLINE operator T&() const BOOST_NOEXCEPT {
        return o_;
    }
private:
    T& o_;
};

template<class T>
struct address_of {
    static BOOST_FORCEINLINE T* get(T& o, long) BOOST_NOEXCEPT {
        return reinterpret_cast<T*>(&
            const_cast<char&>(reinterpret_cast<const volatile char&>(o)));
    }
    static BOOST_FORCEINLINE T* get(T* p, int) BOOST_NOEXCEPT {
        return p;
    }
};

#if !defined(BOOST_NO_CXX11_NULLPTR)
#if !defined(BOOST_NO_CXX11_DECLTYPE) && \
    (defined(__INTEL_COMPILER) || \
        (defined(__clang__) && !defined(_LIBCPP_VERSION)))
typedef decltype(nullptr) null_type;
#else
typedef std::nullptr_t null_type;
#endif

template<>
struct address_of<null_type> {
    typedef null_type type;
    static BOOST_FORCEINLINE type* get(type& o, int) BOOST_NOEXCEPT {
        return &o;
    }
};

template<>
struct address_of<const null_type> {
    typedef const null_type type;
    static BOOST_FORCEINLINE type* get(type& o, int) BOOST_NOEXCEPT {
        return &o;
    }
};

template<>
struct address_of<volatile null_type> {
    typedef volatile null_type type;
    static BOOST_FORCEINLINE type* get(type& o, int) BOOST_NOEXCEPT {
        return &o;
    }
};

template<>
struct address_of<const volatile null_type> {
    typedef const volatile null_type type;
    static BOOST_FORCEINLINE type* get(type& o, int) BOOST_NOEXCEPT {
        return &o;
    }
};
#endif

#if defined(BOOST_CORE_NO_CONSTEXPR_ADDRESSOF)
template<class T>
BOOST_FORCEINLINE T*
addressof(T& o) BOOST_NOEXCEPT
{
#if (defined(__BORLANDC__) && \
        BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610))) || \
    (defined(__SUNPRO_CC) && \
        BOOST_WORKAROUND(__SUNPRO_CC, <= 0x5120))
    return address_of<T>::get(o, 0);
#else
    return address_of<T>::get(addressof_ref<T>(o), 0);
#endif
}
#else
template<class T>
struct add_rvalue_reference {
    typedef T&& type;
};

template<class T>
typename add_rvalue_reference<T>::type declval() BOOST_NOEXCEPT;

template<class>
struct make_void {
    typedef void type;
};

template<class T, class E = void>
struct has_member_address_operator {
    static constexpr bool value = false;
};

template<class T>
struct has_member_address_operator<T,
    typename make_void<decltype(declval<T&>().operator&())>::type> {
    static constexpr bool value = true;
};

#if defined(BOOST_INTEL) && BOOST_WORKAROUND(BOOST_INTEL, < 1600)
struct addressable { };

addressable* operator&(addressable&) BOOST_NOEXCEPT;
#endif

template<class T, class E = void>
struct has_non_member_address_operator {
    static constexpr bool value = false;
};

template<class T>
struct has_non_member_address_operator<T,
    typename make_void<decltype(operator&(declval<T&>()))>::type> {
    static constexpr bool value = true;
};

template<class T, class E = void>
struct is_addressable {
    static constexpr bool value = false;
};

template<class T>
struct is_addressable<T,
    typename make_void<decltype(&declval<T&>())>::type> {
    static constexpr bool value = true;
};

template<class T>
struct has_constexpr_address {
    static constexpr bool value = is_addressable<T>::value &&
        !has_member_address_operator<T>::value &&
        !has_non_member_address_operator<T>::value;
};

template<bool E, class T>
struct address_if { };

template<class T>
struct address_if<true, T> {
    typedef T* type;
};

template<class T>
BOOST_FORCEINLINE
typename address_if<!has_constexpr_address<T>::value, T>::type
addressof(T& o) BOOST_NOEXCEPT
{
    return address_of<T>::get(addressof_ref<T>(o), 0);
}

template<class T>
constexpr BOOST_FORCEINLINE
typename address_if<has_constexpr_address<T>::value, T>::type
addressof(T& o) BOOST_NOEXCEPT
{
    return &o;
}
#endif

} /* detail */
} /* core */

template<class T>
BOOST_CONSTEXPR BOOST_FORCEINLINE T*
addressof(T& o) BOOST_NOEXCEPT
{
    return core::detail::addressof(o);
}

#if defined(BOOST_CORE_NO_CONSTEXPR_ADDRESSOF)
#if defined(__SUNPRO_CC) && \
    BOOST_WORKAROUND(__SUNPRO_CC, BOOST_TESTED_AT(0x590))
namespace core {
namespace detail {

template<class T>
struct add_pointer {
    typedef T* type;
};

} /* detail */
} /* core */

template<class T, std::size_t N>
BOOST_FORCEINLINE typename core::detail::add_pointer<T[N]>::type
addressof(T (&o)[N]) BOOST_NOEXCEPT
{
    return &o;
}
#endif

#if defined(__BORLANDC__) && \
    BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
template<class T, std::size_t N>
BOOST_FORCEINLINE
T (*addressof(T (&o)[N]) BOOST_NOEXCEPT)[N]
{
   return reinterpret_cast<T(*)[N]>(&o);
}

template<class T, std::size_t N>
BOOST_FORCEINLINE
const T (*addressof(const T (&o)[N]) BOOST_NOEXCEPT)[N]
{
   return reinterpret_cast<const T(*)[N]>(&o);
}
#endif
#endif

} /* boost */

#endif
