#ifndef BOOST_REF_HPP_INCLUDED
#define BOOST_REF_HPP_INCLUDED

#if _MSC_VER+0 >= 1020
#pragma once
#endif

//
//  ref.hpp - ref/cref, useful helper functions
//
//  Copyright (C) 1999, 2000 Jaakko Järvi (jaakko.jarvi@cs.utu.fi)
//  Copyright (C) 2001 Peter Dimov
//
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  See http://www.boost.org/libs/bind/ref.html for documentation.
//

namespace boost
{

template<class T> class reference_wrapper
{ 
public:

    explicit reference_wrapper(T & t): t_(t) {}

    operator T & () const { return t_; }

    T & get() const { return t_; }

private:

    T & t_;

    reference_wrapper & operator= (reference_wrapper const &);
};

#if defined(__BORLANDC__) && (__BORLANDC__ <= 0x551)
#define BOOST_REF_CONST
#else
#define BOOST_REF_CONST const
#endif

template<class T> inline reference_wrapper<T> BOOST_REF_CONST ref(T & t)
{ 
    return reference_wrapper<T>(t);
}

template<class T> inline reference_wrapper<T const> BOOST_REF_CONST cref(T const & t)
{
    return reference_wrapper<T const>(t);
}

#undef BOOST_REF_CONST

} // namespace boost

#endif // #ifndef BOOST_REF_HPP_INCLUDED
