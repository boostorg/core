/*
Copyright 2020 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_CORE_ALLOCATOR_ACCESS_HPP
#define BOOST_CORE_ALLOCATOR_ACCESS_HPP

#include <boost/core/pointer_traits.hpp>
#include <limits>
#include <new>
#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
#include <type_traits>
#endif
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#include <utility>
#endif

#if !defined(BOOST_NO_CXX11_DECLTYPE) && \
    !defined(BOOST_NO_SFINAE_EXPR) && \
    (!defined(BOOST_MSVC) || BOOST_MSVC >= 1910)
#define BOOST_CORE_ALLOCATOR_DETECTION
#endif

namespace boost {

template<class A>
struct allocator_value_type {
    typedef typename A::value_type type;
};

namespace detail {

template<class>
struct alloc_void {
    typedef void type;
};

} /* detail */

template<class A, class = void>
struct allocator_pointer {
    typedef typename A::value_type* type;
};

template<class A>
struct allocator_pointer<A,
    typename detail::alloc_void<typename A::pointer>::type> {
    typedef typename A::pointer type;
};

template<class A, class = void>
struct allocator_const_pointer {
    typedef typename pointer_traits<typename
        allocator_pointer<A>::type>::template
            rebind_to<const typename A::value_type>::type type;
};

template<class A>
struct allocator_const_pointer<A,
    typename detail::alloc_void<typename A::const_pointer>::type> {
    typedef typename A::const_pointer type;
};

template<class A, class = void>
struct allocator_void_pointer {
     typedef typename pointer_traits<typename
        allocator_pointer<A>::type>::template
            rebind_to<void>::type type;
};

template<class A>
struct allocator_void_pointer<A,
    typename detail::alloc_void<typename A::void_pointer>::type> {
    typedef typename A::void_pointer type;
};

template<class A, class = void>
struct allocator_const_void_pointer {
     typedef typename pointer_traits<typename
        allocator_pointer<A>::type>::template
            rebind_to<const void>::type type;
};

template<class A>
struct allocator_const_void_pointer<A,
    typename detail::alloc_void<typename A::const_void_pointer>::type> {
    typedef typename A::const_void_pointer type;
};

template<class A, class = void>
struct allocator_difference_type {
    typedef typename pointer_traits<typename
        allocator_pointer<A>::type>::difference_type type;
};

template<class A>
struct allocator_difference_type<A,
    typename detail::alloc_void<typename A::difference_type>::type> {
    typedef typename A::difference_type type;
};

#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
template<class A, class = void>
struct allocator_size_type {
    typedef typename std::make_unsigned<typename
        allocator_difference_type<A>::type>::type type;
};

template<class A>
struct allocator_size_type<A,
    typename detail::alloc_void<typename A::size_type>::type> {
    typedef typename A::size_type type;
};
#else
template<class A>
struct allocator_size_type {
    typedef typename A::size_type type;
};
#endif

namespace detail {

#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
typedef std::false_type alloc_false_type;
#else
struct alloc_false_type {
    BOOST_STATIC_CONSTEXPR bool value = false;
};
#endif

} /* detail */

template<class A, class = void>
struct allocator_propagate_on_container_copy_assignment {
    typedef detail::alloc_false_type type;
};

template<class A>
struct allocator_propagate_on_container_copy_assignment<A,
    typename detail::alloc_void<typename
        A::propagate_on_container_copy_assignment>::type> {
    typedef typename A::propagate_on_container_copy_assignment type;
};

template<class A, class = void>
struct allocator_propagate_on_container_move_assignment {
    typedef detail::alloc_false_type type;
};

template<class A>
struct allocator_propagate_on_container_move_assignment<A,
    typename detail::alloc_void<typename
        A::propagate_on_container_move_assignment>::type> {
    typedef typename A::propagate_on_container_move_assignment type;
};

template<class A, class = void>
struct allocator_propagate_on_container_swap {
    typedef detail::alloc_false_type type;
};

template<class A>
struct allocator_propagate_on_container_swap<A,
    typename detail::alloc_void<typename
        A::propagate_on_container_swap>::type> {
    typedef typename A::propagate_on_container_swap type;
};

#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
template<class A, class = void>
struct allocator_is_always_equal {
    typedef typename std::is_empty<A>::type type;
};
#else
template<class A, class = void>
struct allocator_is_always_equal {
    typedef typename detail::alloc_false_type type;
};
#endif

template<class A>
struct allocator_is_always_equal<A,
    typename detail::alloc_void<typename A::is_always_equal>::type> {
    typedef typename A::is_always_equal type;
};

namespace detail {

template<class, class>
struct alloc_to { };

#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
template<template<class, class...> class A, class T, class U, class... V>
struct alloc_to<A<U, V...>, T> {
    typedef A<T, V...> type;
};
#else
template<template<class> class A, class T, class U>
struct alloc_to<A<U>, T> {
    typedef A<T> type;
};

template<template<class, class> class A, class T, class U1, class U2>
struct alloc_to<A<U1, U2>, T> {
    typedef A<T, U2> type;
};

template<template<class, class, class> class A, class T, class U1, class U2,
    class U3>
struct alloc_to<A<U1, U2, U3>, T> {
    typedef A<T, U2, U3> type;
};
#endif

} /* detail */

template<class A, class T, class = void>
struct allocator_rebind {
    typedef typename detail::alloc_to<A, T>::type type;
};

template<class A, class T>
struct allocator_rebind<A, T,
    typename detail::alloc_void<typename A::template rebind<T>::other>::type> {
    typedef typename A::template rebind<T>::other type;
};

template<class A>
inline typename allocator_pointer<A>::type
allocator_allocate(A& a, typename allocator_size_type<A>::type n)
{
    return a.allocate(n);
}

namespace detail {

template<bool, class = void>
struct alloc_if { };

template<class R>
struct alloc_if<true, R> {
    typedef R type;
};

#if defined(BOOST_CORE_ALLOCATOR_DETECTION)
template<class T>
T alloc_declval() BOOST_NOEXCEPT;
#endif

template<class, class = void>
struct alloc_has_allocate {
    BOOST_STATIC_CONSTEXPR bool value = false;
};

#if defined(BOOST_CORE_ALLOCATOR_DETECTION)
template<class A>
struct alloc_has_allocate<A, typename
    alloc_void<decltype(alloc_declval<A&>().allocate(alloc_declval<typename
        boost::allocator_size_type<A>::type>(), alloc_declval<typename
            boost::allocator_const_void_pointer<A>::type>()))>::type> {
    BOOST_STATIC_CONSTEXPR bool value = true;
};
#endif

} /* detail */

template<class A>
inline typename detail::alloc_if<detail::alloc_has_allocate<A>::value,
    typename allocator_pointer<A>::type>::type
allocator_allocate(A& a, typename allocator_size_type<A>::type n,
    typename allocator_const_void_pointer<A>::type h)
{
    return a.allocate(n, h);
}

template<class A>
inline typename detail::alloc_if<!detail::alloc_has_allocate<A>::value,
    typename allocator_pointer<A>::type>::type
allocator_allocate(A& a, typename allocator_size_type<A>::type n,
    typename allocator_const_void_pointer<A>::type)
{
    return a.allocate(n);
}

template<class A>
inline void
allocator_deallocate(A& a, typename allocator_pointer<A>::type p,
    typename allocator_size_type<A>::type n)
{
    a.deallocate(p, n);
}

namespace detail {

#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
template<class...>
struct alloc_types { };
#else
template<class>
struct alloc_types { };
#endif

template<class, class, class, class = void>
struct alloc_has_construct {
    BOOST_STATIC_CONSTEXPR bool value = false;
};

#if defined(BOOST_CORE_ALLOCATOR_DETECTION)
#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
template<class A, class T, class... U>
struct alloc_has_construct<A, T, alloc_types<U...>, typename
    alloc_void<decltype(alloc_declval<A&>().construct(alloc_declval<T*>(),
        alloc_declval<U>()...))>::type> {
    BOOST_STATIC_CONSTEXPR bool value = true;
};
#else
template<class A, class T, class U>
struct alloc_has_construct<A, T, alloc_types<U>, typename
    alloc_void<decltype(alloc_declval<A&>().construct(alloc_declval<T*>(),
        alloc_declval<U>()))>::type> {
    BOOST_STATIC_CONSTEXPR bool value = true;
};
#endif
#endif

} /* detail */

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
template<class A, class T, class... Args>
inline typename detail::alloc_if<detail::alloc_has_construct<A, T,
    detail::alloc_types<Args...> >::value>::type
allocator_construct(A& a, T*p, Args&&... args)
{
    a.construct(p, std::forward<Args>(args)...);
}

template<class A, class T, class... Args>
inline typename detail::alloc_if<!detail::alloc_has_construct<A, T,
    detail::alloc_types<Args...> >::value>::type
allocator_construct(A&, T* p, Args&&... args)
{
    ::new(static_cast<void*>(p)) T(std::forward<Args>(args)...);
}
#else
template<class A, class T, class V>
inline typename detail::alloc_if<detail::alloc_has_construct<A, T,
    detail::alloc_types<V> >::value>::type
allocator_construct(A& a, T*p, V&& v)
{
    a.construct(p, std::forward<V>(v));
}

template<class A, class T, class V>
inline typename detail::alloc_if<!detail::alloc_has_construct<A, T,
    detail::alloc_types<V> >::value>::type
allocator_construct(A&, T* p, V&& v)
{
    ::new(static_cast<void*>(p)) T(std::forward<V>(v));
}
#endif
#else
template<class A, class T, class V>
inline typename detail::alloc_if<detail::alloc_has_construct<A, T,
    detail::alloc_types<V> >::value>::type
allocator_construct(A& a, T*p, const V& v)
{
    a.construct(p, v);
}

template<class A, class T, class V>
inline typename detail::alloc_if<!detail::alloc_has_construct<A, T,
    detail::alloc_types<V> >::value>::type
allocator_construct(A&, T* p, const V& v)
{
    ::new(static_cast<void*>(p)) T(v);
}

template<class A, class T, class V>
inline typename detail::alloc_if<detail::alloc_has_construct<A, T,
    detail::alloc_types<V> >::value>::type
allocator_construct(A& a, T*p, V& v)
{
    a.construct(p, v);
}

template<class A, class T, class V>
inline typename detail::alloc_if<!detail::alloc_has_construct<A, T,
    detail::alloc_types<V> >::value>::type
allocator_construct(A&, T* p, V& v)
{
    ::new(static_cast<void*>(p)) T(v);
}
#endif

namespace detail {

template<class, class, class = void>
struct alloc_has_destroy {
    BOOST_STATIC_CONSTEXPR bool value = false;
};

#if defined(BOOST_CORE_ALLOCATOR_DETECTION)
template<class A, class T>
struct alloc_has_destroy<A, T, typename
    alloc_void<decltype(alloc_declval<A&>().
        destroy(alloc_declval<T*>()))>::type> {
    BOOST_STATIC_CONSTEXPR bool value = true;
};
#endif

} /* detail */

template<class A, class T>
inline typename detail::alloc_if<detail::alloc_has_destroy<A, T>::value>::type
allocator_destroy(A& a, T*p)
{
    a.destroy(p);
}

template<class A, class T>
inline typename detail::alloc_if<!detail::alloc_has_destroy<A, T>::value>::type
allocator_destroy(A&, T* p)
{
    p->~T();
    (void)p;
}

namespace detail {

template<class, class = void>
struct alloc_has_max_size {
    BOOST_STATIC_CONSTEXPR bool value = false;
};

#if defined(BOOST_CORE_ALLOCATOR_DETECTION)
template<class A>
struct alloc_has_max_size<A,
    typename alloc_void<decltype(alloc_declval<const
        A&>().max_size())>::type> {
    BOOST_STATIC_CONSTEXPR bool value = true;
};
#endif

} /* detail */

template<class A>
inline typename detail::alloc_if<detail::alloc_has_max_size<A>::value,
    typename allocator_size_type<A>::type>::type
allocator_max_size(const A& a)
{
    return a.max_size();
}

template<class A>
inline typename detail::alloc_if<!detail::alloc_has_max_size<A>::value,
    typename allocator_size_type<A>::type>::type
allocator_max_size(const A&)
{
    return std::numeric_limits<typename allocator_size_type<A>::type>::max() /
        sizeof(typename A::value_type);
}

namespace detail {

template<class, class = void>
struct alloc_has_soccc {
    BOOST_STATIC_CONSTEXPR bool value = false;
};

#if defined(BOOST_CORE_ALLOCATOR_DETECTION)
template<class A>
struct alloc_has_soccc<A,
    typename alloc_void<decltype(alloc_declval<const
        A&>().select_on_container_copy_construction())>::type> {
    BOOST_STATIC_CONSTEXPR bool value = true;
};
#endif

} /* detail */

template<class A>
inline typename detail::alloc_if<detail::alloc_has_soccc<A>::value, A>::type
allocator_select_on_container_copy_construction(const A& a)
{
    return a.select_on_container_copy_construction();
}

template<class A>
inline typename detail::alloc_if<!detail::alloc_has_soccc<A>::value, A>::type
allocator_select_on_container_copy_construction(const A& a)
{
    return a;
}

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)
template<class A>
using allocator_value_type_t = typename allocator_value_type<A>::type;

template<class A>
using allocator_pointer_t = typename allocator_pointer<A>::type;

template<class A>
using allocator_const_pointer_t = typename allocator_const_pointer<A>::type;

template<class A>
using allocator_void_pointer_t = typename allocator_void_pointer<A>::type;

template<class A>
using allocator_const_void_pointer_t =
    typename allocator_const_void_pointer<A>::type;

template<class A>
using allocator_difference_type_t =
    typename allocator_difference_type<A>::type;

template<class A>
using allocator_size_type_t = typename allocator_size_type<A>::type;

template<class A>
using allocator_propagate_on_container_copy_assignment_t =
    typename allocator_propagate_on_container_copy_assignment<A>::type;

template<class A>
using allocator_propagate_on_container_move_assignment_t =
    typename allocator_propagate_on_container_move_assignment<A>::type;

template<class A>
using allocator_propagate_on_container_swap_t =
    typename allocator_propagate_on_container_swap<A>::type;

template<class A>
using allocator_is_always_equal_t =
    typename allocator_is_always_equal<A>::type;

template<class A, class T>
using allocator_rebind_t = typename allocator_rebind<A, T>::type;
#endif

} /* boost */

#endif
