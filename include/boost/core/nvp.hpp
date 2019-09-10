/*
Copyright 2019 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_CORE_NVP_HPP
#define BOOST_CORE_NVP_HPP

#include <boost/core/addressof.hpp>
#include <boost/config.hpp>

namespace boost {
namespace detail {

template<bool V>
struct nvp_bool {
    typedef bool value_type;
    typedef nvp_bool type;

    BOOST_STATIC_CONSTEXPR bool value = V;

    BOOST_CONSTEXPR operator bool() const BOOST_NOEXCEPT {
        return V;
    }

    BOOST_CONSTEXPR bool operator()() const BOOST_NOEXCEPT {
        return V;
    }
};

template<bool V>
BOOST_CONSTEXPR_OR_CONST bool nvp_bool<V>::value;

} /* detail */

template<class T>
class nvp {
public:
    nvp(const char* n, T& v) BOOST_NOEXCEPT
        : n_(n)
        , v_(boost::addressof(v)) { }

    const char* name() const BOOST_NOEXCEPT {
        return n_;
    }

    T& value() const BOOST_NOEXCEPT {
        return *v_;
    }

    const T& const_value() const BOOST_NOEXCEPT {
        return *v_;
    }

    template<class A>
    void serialize(A& a, unsigned) {
        archive(a, detail::nvp_bool<A::is_saving::value>());
    }

private:
    template<class A>
    void archive(A& a, detail::nvp_bool<true>) const {
        a.operator<<(*v_);
    }

    template<class A>
    void archive(A& a, detail::nvp_bool<false>) {
        a.operator>>(*v_);
    }

    const char* n_;
    T* v_;
};

template<class>
struct is_nvp
    : detail::nvp_bool<false> { };

template<class T>
struct is_nvp<nvp<T> >
    : detail::nvp_bool<true> { };

template<class T>
struct is_nvp<const nvp<T> >
    : detail::nvp_bool<true> { };

template<class T>
struct is_nvp<volatile nvp<T> >
    : detail::nvp_bool<true> { };

template<class T>
struct is_nvp<const volatile nvp<T> >
    : detail::nvp_bool<true> { };

template<class T>
inline const nvp<T>
make_nvp(const char* n, T& v) BOOST_NOEXCEPT
{
    return nvp<T>(n, v);
}

} /* boost */

#endif
