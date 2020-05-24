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
#if defined(BOOST_DINKUMWARE_STDLIB)
#include <memory>
#endif
#include <new>
#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
#include <type_traits>
#endif
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#include <utility>
#endif

#if !defined(BOOST_NO_CXX11_DECLTYPE) && !defined(BOOST_NO_SFINAE_EXPR) || \
    defined(BOOST_MSVC) && BOOST_MSVC == 1800
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

template<class>
struct alloc_enable {
    BOOST_STATIC_CONSTEXPR bool value = true;
};

#if defined(BOOST_DINKUMWARE_STDLIB)
template<class T>
struct alloc_enable<std::allocator<T> > {
    BOOST_STATIC_CONSTEXPR bool value = false;
};
#endif

#if defined(BOOST_CORE_ALLOCATOR_DETECTION)
template<class T>
T alloc_declval() BOOST_NOEXCEPT;
#endif

#if defined(BOOST_MSVC) && BOOST_MSVC == 1800
template<class>
struct alloc_yes {
    BOOST_STATIC_CONSTEXPR bool value = true;
};

struct alloc_no {
    BOOST_STATIC_CONSTEXPR bool value = false;
};
#endif

template<class, class, class, class = void>
struct alloc_has_allocate {
    BOOST_STATIC_CONSTEXPR bool value = false;
};

#if !defined(BOOST_NO_CXX11_DECLTYPE) && !defined(BOOST_NO_SFINAE_EXPR)
template<class A, class N, class H>
struct alloc_has_allocate<A, N, H,
    decltype(alloc_declval<A&>().allocate(alloc_declval<N>(),
        alloc_declval<H>()), void())> {
    BOOST_STATIC_CONSTEXPR bool value = true;
};
#elif defined(BOOST_MSVC) && BOOST_MSVC == 1800
template<class A, class N, class H>
struct alloc_has_allocate<A, N, H, void> {
private:
    template<class U>
    static auto call(int, U& a) ->
        alloc_yes<decltype(a.allocate(alloc_declval<N>(),
            alloc_declval<H>()))>;

    template<class U>
    static alloc_no call(long, U&);

public:
    BOOST_STATIC_CONSTEXPR bool value = decltype(call(0,
        alloc_declval<A&>()))::value;
};
#endif

} /* detail */

template<class A>
inline typename detail::alloc_if<detail::alloc_enable<A>::value &&
    detail::alloc_has_allocate<A, typename allocator_size_type<A>::type,
        typename allocator_const_void_pointer<A>::type>::value,
            typename allocator_pointer<A>::type>::type
allocator_allocate(A& a, typename allocator_size_type<A>::type n,
    typename allocator_const_void_pointer<A>::type h)
{
    return a.allocate(n, h);
}

template<class A>
inline typename detail::alloc_if<!detail::alloc_enable<A>::value ||
    !detail::alloc_has_allocate<A, typename allocator_size_type<A>::type,
        typename allocator_const_void_pointer<A>::type>::value,
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

template<class, class, class = void>
struct alloc_has_construct {
    BOOST_STATIC_CONSTEXPR bool value = false;
};

#if !defined(BOOST_NO_CXX11_DECLTYPE) && !defined(BOOST_NO_SFINAE_EXPR)
template<class A, class T>
struct alloc_has_construct<A, T,
    decltype(alloc_declval<A&>().construct(alloc_declval<T*>()), void())> {
    BOOST_STATIC_CONSTEXPR bool value = true;
};
#elif defined(BOOST_MSVC) && BOOST_MSVC == 1800
template<class A, class T>
struct alloc_has_construct<A, T, void> {
private:
    template<class U>
    static auto call(int, U& a) ->
        alloc_yes<decltype(a.construct(alloc_declval<T*>()))>;

    template<class U>
    static alloc_no call(long, U&);

public:
    BOOST_STATIC_CONSTEXPR bool value = decltype(call(0,
        alloc_declval<A&>()))::value;
};
#endif

} /* detail */

template<class A, class T>
inline typename detail::alloc_if<detail::alloc_enable<A>::value &&
    detail::alloc_has_construct<A, T>::value>::type
allocator_construct(A& a, T* p)
{
    a.construct(p);
}

template<class A, class T>
inline typename detail::alloc_if<!detail::alloc_enable<A>::value ||
    !detail::alloc_has_construct<A, T>::value>::type
allocator_construct(A&, T* p)
{
    ::new((void*)p) T();
}

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && \
    !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
namespace detail {

template<class, class, class, class...>
struct alloc_has_construct_args {
    BOOST_STATIC_CONSTEXPR bool value = false;
};

#if !defined(BOOST_NO_CXX11_DECLTYPE) && !defined(BOOST_NO_SFINAE_EXPR)
template<class A, class T, class... Args>
struct alloc_has_construct_args<decltype(alloc_declval<A
    &>().construct(alloc_declval<T*>(), alloc_declval<Args&&>()...), void()),
        A, T, Args...> {
    BOOST_STATIC_CONSTEXPR bool value = true;
};
#elif defined(BOOST_MSVC) && BOOST_MSVC == 1800
template<class A, class T, class... Args>
struct alloc_has_construct_args<void, A, T, Args...> {
private:
    template<class U>
    static auto call(int, U& a) ->
        alloc_yes<decltype(a.construct(alloc_declval<T*>(),
            alloc_declval<Args&&>()...))>;

    template<class U>
    static alloc_no call(long, U&);

public:
    BOOST_STATIC_CONSTEXPR bool value = decltype(call(0,
        alloc_declval<A&>()))::value;
};
#endif

} /* detail */

template<class A, class T, class V, class... Args>
inline typename detail::alloc_if<detail::alloc_enable<A>::value &&
    detail::alloc_has_construct_args<void, A, T, V, Args...>::value>::type
allocator_construct(A& a, T* p, V&& v, Args&&... args)
{
    a.construct(p, std::forward<V>(v), std::forward<Args>(args)...);
}

template<class A, class T, class V, class... Args>
inline typename detail::alloc_if<!detail::alloc_enable<A>::value ||
    !detail::alloc_has_construct_args<void, A, T, V, Args...>::value>::type
allocator_construct(A&, T* p, V&& v, Args&&... args)
{
    ::new((void*)p) T(std::forward<V>(v), std::forward<Args>(args)...);
}
#else
namespace detail {

template<class, class, class, class = void>
struct alloc_has_construct_arg {
    BOOST_STATIC_CONSTEXPR bool value = false;
};

#if !defined(BOOST_NO_CXX11_DECLTYPE) && !defined(BOOST_NO_SFINAE_EXPR)
template<class A, class T, class V>
struct alloc_has_construct_arg<A, T, V,
    decltype(alloc_declval<A&>().construct(alloc_declval<T*>(),
        alloc_declval<V>()), void())> {
    BOOST_STATIC_CONSTEXPR bool value = true;
};
#elif defined(BOOST_MSVC) && BOOST_MSVC == 1800
template<class A, class T, class V>
struct alloc_has_construct_arg<A, T, V, void> {
private:
    template<class U>
    static auto call(int, U& a) ->
        alloc_yes<decltype(a.construct(alloc_declval<T*>(),
            alloc_declval<V>()))>;

    template<class U>
    static alloc_no call(long, U&);

public:
    BOOST_STATIC_CONSTEXPR bool value = decltype(call(0,
        alloc_declval<A&>()))::value;
};
#endif

} /* detail */

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
template<class A, class T, class V>
inline typename detail::alloc_if<detail::alloc_enable<A>::value &&
    detail::alloc_has_construct_arg<A, T, V&&>::value>::type
allocator_construct(A& a, T* p, V&& v)
{
    a.construct(p, std::forward<V>(v));
}

template<class A, class T, class V>
inline typename detail::alloc_if<!detail::alloc_enable<A>::value ||
    !detail::alloc_has_construct_arg<A, T, V&&>::value>::type
allocator_construct(A&, T* p, V&& v)
{
    ::new((void*)p) T(std::forward<V>(v));
}
#else
template<class A, class T, class V>
inline typename detail::alloc_if<detail::alloc_enable<A>::value &&
    detail::alloc_has_construct_arg<A, T, const V&>::value>::type
allocator_construct(A& a, T* p, const V& v)
{
    a.construct(p, v);
}

template<class A, class T, class V>
inline typename detail::alloc_if<!detail::alloc_enable<A>::value ||
    !detail::alloc_has_construct_arg<A, T, const V&>::value>::type
allocator_construct(A&, T* p, const V& v)
{
    ::new((void*)p) T(v);
}

template<class A, class T, class V>
inline typename detail::alloc_if<detail::alloc_enable<A>::value &&
    detail::alloc_has_construct_arg<A, T, V&>::value>::type
allocator_construct(A& a, T* p, V& v)
{
    a.construct(p, v);
}

template<class A, class T, class V>
inline typename detail::alloc_if<!detail::alloc_enable<A>::value ||
    !detail::alloc_has_construct_arg<A, T, V&>::value>::type
allocator_construct(A&, T* p, V& v)
{
    ::new((void*)p) T(v);
}
#endif
#endif

namespace detail {

template<class, class, class = void>
struct alloc_has_destroy {
    BOOST_STATIC_CONSTEXPR bool value = false;
};

#if !defined(BOOST_NO_CXX11_DECLTYPE) && !defined(BOOST_NO_SFINAE_EXPR)
template<class A, class T>
struct alloc_has_destroy<A, T,
    decltype(alloc_declval<A&>().destroy(alloc_declval<T*>()), void())> {
    BOOST_STATIC_CONSTEXPR bool value = true;
};
#elif defined(BOOST_MSVC) && BOOST_MSVC == 1800
template<class A, class T>
struct alloc_has_destroy<A, T, void> {
private:
    template<class U>
    static auto call(int, U& a) ->
        alloc_yes<decltype(a.destroy(alloc_declval<T*>()))>;

    template<class U>
    static alloc_no call(long, U&);

public:
    BOOST_STATIC_CONSTEXPR bool value = decltype(call(0,
        alloc_declval<A&>()))::value;
};
#endif

} /* detail */

template<class A, class T>
inline typename detail::alloc_if<detail::alloc_enable<A>::value &&
    detail::alloc_has_destroy<A, T>::value>::type
allocator_destroy(A& a, T* p)
{
    a.destroy(p);
}

template<class A, class T>
inline typename detail::alloc_if<!detail::alloc_enable<A>::value ||
    !detail::alloc_has_destroy<A, T>::value>::type
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

#if !defined(BOOST_NO_CXX11_DECLTYPE) && !defined(BOOST_NO_SFINAE_EXPR)
template<class A>
struct alloc_has_max_size<A,
    decltype(alloc_declval<const A&>().max_size(), void())> {
    BOOST_STATIC_CONSTEXPR bool value = true;
};
#elif defined(BOOST_MSVC) && BOOST_MSVC == 1800
template<class A>
struct alloc_has_max_size<A, void> {
private:
    template<class U>
    static auto call(int, const U& a) -> alloc_yes<decltype(a.max_size())>;

    template<class U>
    static alloc_no call(long, const U&);

public:
    BOOST_STATIC_CONSTEXPR bool value = decltype(call(0,
        alloc_declval<const A&>()))::value;
};
#endif

} /* detail */

template<class A>
inline typename detail::alloc_if<detail::alloc_enable<A>::value &&
    detail::alloc_has_max_size<A>::value,
        typename allocator_size_type<A>::type>::type
allocator_max_size(const A& a)
{
    return a.max_size();
}

template<class A>
inline typename detail::alloc_if<!detail::alloc_enable<A>::value ||
    !detail::alloc_has_max_size<A>::value,
        typename allocator_size_type<A>::type>::type
allocator_max_size(const A&)
{
    return (std::numeric_limits<typename
        allocator_size_type<A>::type>::max)() / sizeof(typename A::value_type);
}

namespace detail {

template<class, class = void>
struct alloc_has_soccc {
    BOOST_STATIC_CONSTEXPR bool value = false;
};

#if !defined(BOOST_NO_CXX11_DECLTYPE) && !defined(BOOST_NO_SFINAE_EXPR)
template<class A>
struct alloc_has_soccc<A,
    decltype(alloc_declval<const A&>().select_on_container_copy_construction(),
        void())> {
    BOOST_STATIC_CONSTEXPR bool value = true;
};
#elif defined(BOOST_MSVC) && BOOST_MSVC == 1800
template<class A>
struct alloc_has_soccc<A, void> {
private:
    template<class U>
    static auto call(int, const U& a) ->
        alloc_yes<decltype(a.select_on_container_copy_construction())>;

    template<class U>
    static alloc_no call(long, const U&);

public:
    BOOST_STATIC_CONSTEXPR bool value = decltype(call(0,
        alloc_declval<const A&>()))::value;
};
#endif

} /* detail */

template<class A>
inline typename detail::alloc_if<detail::alloc_enable<A>::value &&
    detail::alloc_has_soccc<A>::value, A>::type
allocator_select_on_container_copy_construction(const A& a)
{
    return a.select_on_container_copy_construction();
}

template<class A>
inline typename detail::alloc_if<!detail::alloc_enable<A>::value ||
    !detail::alloc_has_soccc<A>::value, A>::type
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
