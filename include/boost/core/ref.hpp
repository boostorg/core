#ifndef BOOST_CORE_REF_HPP
#define BOOST_CORE_REF_HPP

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/config.hpp>
#include <boost/utility/addressof.hpp>
#include <boost/detail/workaround.hpp>

//
//  ref.hpp - ref/cref, useful helper functions
//
//  Copyright (C) 1999, 2000 Jaakko Jarvi (jaakko.jarvi@cs.utu.fi)
//  Copyright (C) 2001, 2002 Peter Dimov
//  Copyright (C) 2002 David Abrahams
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/bind/ref.html for documentation.
//

namespace boost
{

// reference_wrapper

template<class T> class reference_wrapper
{
public:
    typedef T type;

    BOOST_FORCEINLINE explicit reference_wrapper(T& t): t_(boost::addressof(t)) {}

    BOOST_FORCEINLINE operator T& () const { return *t_; }

    BOOST_FORCEINLINE T& get() const { return *t_; }

    BOOST_FORCEINLINE T* get_pointer() const { return t_; }

private:

    T* t_;
};

// ref

# if defined( __BORLANDC__ ) && BOOST_WORKAROUND( __BORLANDC__, BOOST_TESTED_AT(0x581) )
#  define BOOST_REF_CONST
# else
#  define BOOST_REF_CONST const
# endif

template<class T> BOOST_FORCEINLINE reference_wrapper<T> BOOST_REF_CONST ref( T & t )
{
    return reference_wrapper<T>(t);
}

// cref

template<class T> BOOST_FORCEINLINE reference_wrapper<T const> BOOST_REF_CONST cref( T const & t )
{
    return reference_wrapper<T const>(t);
}

# undef BOOST_REF_CONST

// is_reference_wrapper

template<typename T> struct is_reference_wrapper
{
    BOOST_STATIC_CONSTANT( bool, value = false );
};

template<typename T> struct is_reference_wrapper< reference_wrapper<T> >
{
    BOOST_STATIC_CONSTANT( bool, value = true );
};

#if !defined(BOOST_NO_CV_SPECIALIZATIONS)

template<typename T> struct is_reference_wrapper< reference_wrapper<T> const >
{
    BOOST_STATIC_CONSTANT( bool, value = true );
};

template<typename T> struct is_reference_wrapper< reference_wrapper<T> volatile >
{
    BOOST_STATIC_CONSTANT( bool, value = true );
};

template<typename T> struct is_reference_wrapper< reference_wrapper<T> const volatile >
{
    BOOST_STATIC_CONSTANT( bool, value = true );
};

#endif // !defined(BOOST_NO_CV_SPECIALIZATIONS)

// unwrap_reference

template<typename T> struct unwrap_reference
{
    typedef T type;
};

template<typename T> struct unwrap_reference< reference_wrapper<T> >
{
    typedef T type;
};

#if !defined(BOOST_NO_CV_SPECIALIZATIONS)

template<typename T> struct unwrap_reference< reference_wrapper<T> const >
{
    typedef T type;
};

template<typename T> struct unwrap_reference< reference_wrapper<T> volatile >
{
    typedef T type;
};

template<typename T> struct unwrap_reference< reference_wrapper<T> const volatile >
{
    typedef T type;
};

#endif // !defined(BOOST_NO_CV_SPECIALIZATIONS)

// unwrap_ref

template<class T> BOOST_FORCEINLINE typename unwrap_reference<T>::type& unwrap_ref( T & t )
{
    return t;
}

// get_pointer

template<class T> BOOST_FORCEINLINE T* get_pointer( reference_wrapper<T> const & r )
{
    return r.get_pointer();
}

} // namespace boost

#endif // #ifndef BOOST_CORE_REF_HPP
