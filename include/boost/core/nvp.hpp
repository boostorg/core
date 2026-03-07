/*
Copyright 2019 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_CORE_NVP_HPP
#define BOOST_CORE_NVP_HPP

#if defined(BOOST_USE_MODULES) && !defined(BOOST_CORE_INTERFACE_UNIT)
#ifndef BOOST_IN_MODULE_PURVIEW
import boost.core;
#endif
#else

#include <boost/core/detail/modules.hpp>
#include <boost/core/addressof.hpp>
#include <boost/config.hpp>

namespace boost {
namespace serialization {

BOOST_CORE_MODULE_EXPORT template<class T>
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

private:
    const char* n_;
    T* v_;
};

BOOST_CORE_MODULE_EXPORT template<class T>
inline const nvp<T>
make_nvp(const char* n, T& v) BOOST_NOEXCEPT
{
    return nvp<T>(n, v);
}

} /* serialization */

BOOST_CORE_MODULE_EXPORT using serialization::nvp;
BOOST_CORE_MODULE_EXPORT using serialization::make_nvp;

} /* boost */

#endif // defined(BOOST_USE_MODULES) && !defined(BOOST_CORE_INTERFACE_UNIT)

// Export the macro even in builds with modules
#define BOOST_NVP(v) boost::make_nvp(BOOST_STRINGIZE(v), v)

#endif
