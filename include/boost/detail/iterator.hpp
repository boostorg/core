// (C) Copyright David Abrahams 2001. Permission to copy, use, modify,
// sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

// Boost versions of
//
//    std::iterator_traits<>::iterator_category
//    std::iterator_traits<>::difference_type
//    std::distance()
//
// ...for all compilers and iterators

#ifndef ITERATOR_DWA122600_HPP_
# define ITERATOR_DWA122600_HPP_

# include <boost/config.hpp>
# include <boost/type_traits.hpp>
# include <iterator>
# include <cstddef>

// STLPort 4.0 and betas have a bug when debugging is enabled and there is no
// partial specialization: instead of an iterator_category typedef, the standard
// container iterators have _Iterator_category.
//
// Also, whether debugging is enabled or not, there is a broken specialization
// of std::iterator<output_iterator_tag,void,void,void,void> which has no
// typedefs but iterator_category.
# if defined(__SGI_STL_PORT) && (__SGI_STL_PORT <= 0x410) && !defined(__STL_CLASS_PARTIAL_SPECIALIZATION)

#  ifdef __STL_DEBUG
#   define BOOST_BAD_CONTAINER_ITERATOR_CATEGORY_TYPEDEF
#  endif

#  define BOOST_BAD_OUTPUT_ITERATOR_SPECIALIZATION

# endif // STLPort <= 4.1b4 && no partial specialization

# ifdef BOOST_BAD_CONTAINER_ITERATOR_CATEGORY_TYPEDEF
#  include <vector>
#  include <list>
#  include <set>
#  include <map>
#  include <deque>
#  include <slist>
#  include <hash_map>
#  include <hash_set>
#  include <string>
# endif

namespace boost { namespace detail {
# if !defined(BOOST_NO_STD_ITERATOR_TRAITS) && !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
using std::iterator_traits;
using std::distance;
# else
// Workarounds for less-capable implementations
template <bool is_ptr> struct iterator_traits_select;
template <> struct iterator_traits_select<true>
{
    template <class Ptr>
    struct traits
    {
        typedef std::ptrdiff_t difference_type;
        typedef std::random_access_iterator_tag iterator_category;
    };
};


# ifdef BOOST_BAD_CONTAINER_ITERATOR_CATEGORY_TYPEDEF
no_result bad_category_helper(...);
template <class C, class T> yes_result bad_category_helper(std::_DBG_iter<C,T>*);

template <bool has_bad_category_typedef> struct bad_category_select;
template <>
struct bad_category_select<true>
{
    template <class Iterator>
    struct category { typedef typename Iterator::_Iterator_category type; };
};
template <>
struct bad_category_select<false>
{
    template <class Iterator>
    struct category { typedef typename Iterator::iterator_category type; };
};

template <class Iterator>
struct iterator_category_select
{
 private:
    static Iterator p;
    enum { has_bad_category
           = sizeof(bad_category_helper(&p)) == sizeof(yes_result) };
    typedef bad_category_select<has_bad_category> category_select;
 public:
    typedef typename category_select::template category<Iterator>::type type;
};

# endif

# ifdef BOOST_BAD_OUTPUT_ITERATOR_SPECIALIZATION
template <bool is_bad_output_iterator> struct bad_difference_select;
template <>
struct bad_difference_select<true>
{
    template <class Iterator>
    struct difference { typedef void type; };
};
template <>
struct bad_difference_select<false>
{
    template <class Iterator>
    struct difference { typedef typename Iterator::difference_type type; };
};
yes_result bad_output_iterator_helper(std::iterator<std::output_iterator_tag,void,void,void,void>*);
no_result bad_output_iterator_helper(...);
# endif

template <> struct iterator_traits_select<false>
{
    template <class Iterator>
    struct traits
#  if defined(BOOST_NO_STD_ITERATOR_TRAITS)
    {
#   if defined(BOOST_MSVC) && !defined(__SGI_STL_PORT)
        typedef typename Iterator::distance_type difference_type;
#   elif !defined(BOOST_BAD_OUTPUT_ITERATOR_SPECIALIZATION)
        typedef typename Iterator::difference_type difference_type;
#   else
     private:
        // static Iterator *p;
        typedef bad_difference_select<
          is_convertible<const volatile Iterator*,
            const volatile std::iterator<std::output_iterator_tag,void,void,void,void>*
          >::value> difference_type_select;
     public:
        typedef typename difference_type_select::template difference<Iterator>::type difference_type;
#   endif
        
#   if !defined(BOOST_BAD_CONTAINER_ITERATOR_CATEGORY_TYPEDEF)
        typedef typename Iterator::iterator_category iterator_category;
#   else
        typedef typename iterator_category_select<Iterator>::type iterator_category;
#   endif
    };
#  else
    {
        typedef typename std::iterator_traits<Iterator>::difference_type difference_type;
        typedef typename std::iterator_traits<Iterator>::iterator_category iterator_category;
    };
#  endif
};

template <class Iterator>
struct iterator_traits
{
 private:
    typedef iterator_traits_select<is_pointer<remove_cv<Iterator>::type>::value> select;
    typedef typename select::template traits<Iterator> traits;
 public:
    typedef typename traits::difference_type difference_type;
    typedef typename traits::iterator_category iterator_category;
};

template <class Category>
struct distance_select {
    template <class Iterator>
    static typename ::boost::detail::iterator_traits<Iterator>::difference_type
    distance(Iterator i1, const Iterator i2)
    {
        typename ::boost::detail::iterator_traits<Iterator>::difference_type result = 0;
        while (i1 != i2)
        {
            ++i1;
            ++result;
        }
        return result;
    }
};

template <>
struct distance_select<std::random_access_iterator_tag> {
    template <class Iterator>
    static typename ::boost::detail::iterator_traits<Iterator>::difference_type
    distance(const Iterator i1, const Iterator i2)
    {
        return i2 - i1;
    }
};

template <class Iterator>
inline typename ::boost::detail::iterator_traits<Iterator>::difference_type
distance(const Iterator& first, const Iterator& last)
{
    typedef typename ::boost::detail::iterator_traits<Iterator>::iterator_category iterator_category;
    return distance_select<iterator_category>::distance(first, last);
}
# endif // workarounds

}}

# undef BOOST_BAD_CONTAINER_ITERATOR_CATEGORY_TYPEDEF
# undef BOOST_BAD_OUTPUT_ITERATOR_SPECIALIZATION

#endif // ITERATOR_DWA122600_HPP_
