#if defined(_MSC_VER) && !defined(__ICL)
# pragma warning(disable: 4786)  // identifier truncated in debug info
# pragma warning(disable: 4710)  // function not inlined
# pragma warning(disable: 4711)  // function selected for automatic inline expansion
# pragma warning(disable: 4514)  // unreferenced inline removed
#endif

#include <boost/ref.hpp>
#include <boost/type_traits.hpp>
#include <boost/pending/ct_if.hpp>

#if defined(BOOST_MSVC) && (BOOST_MSVC < 1300)
# pragma warning(push, 3)
#endif

#include <iostream>

#if defined(BOOST_MSVC) && (BOOST_MSVC < 1300)
# pragma warning(pop)
#endif


#define BOOST_INCLUDE_MAIN
#include <boost/test/test_tools.hpp>

namespace {
using namespace boost;

template <class T>
struct wrapper
{
    // Used to verify implicit conversion
    static T* get_pointer(T& x)
    {
        return &x;
    }

    static T const* get_const_pointer(T const& x)
    {
        return &x;
    }

    static void check_type_typedef(...)
    {
        BOOST_ERROR("expected a reference_wrapper argument");
    }
    
    template <class U>
    static void check_type_typedef(boost::reference_wrapper<U>)
    {
        typedef typename boost::reference_wrapper<U>::type type_typedef;
        BOOST_TEST((boost::is_same<type_typedef,U>::value));
    }
    
    template <class Arg>
    static T* passthru(Arg x)
    {
        check_type_typedef(x);
        return get_pointer(x);
    }

    template <class Arg>
    static T const* cref_passthru(Arg x)
    {
        check_type_typedef(x);
        return get_const_pointer(x);
    }

    template <class Arg>
    static void test_unwrapped(Arg x)
    {
        typedef typename unwrap_reference<Arg>::type unwrapped;
        BOOST_TEST((is_same<Arg,unwrapped>::value));
    }

    template <bool is_constant> struct select {};
    typedef select<true> constant;
    typedef select<false> non_constant;
    
    static void cref_test(T x, constant) {}
    
    static void cref_test(T x, non_constant)
    {
        BOOST_TEST(is_reference_wrapper<reference_wrapper<T const> >::value);
        BOOST_TEST(cref_passthru(cref(x)) == &x);
        BOOST_TEST(&cref(x).get() == &x);
    }

    BOOST_STATIC_CONSTANT(
        bool, t_is_constant = boost::is_const<T>::value);

    static void test(T x)
    {
        BOOST_TEST(passthru(ref(x)) == &x);
        
        BOOST_TEST((is_same<reference_wrapper<T>::type,T>::value));
        
        BOOST_TEST(&ref(x).get() == &x);

        typedef reference_wrapper<T> wrapped;
        BOOST_TEST(is_reference_wrapper<wrapped>::value);
        
        typedef typename unwrap_reference<wrapped>::type unwrapped_wrapper;
        BOOST_TEST((is_same<T,unwrapped_wrapper>::value));

        typedef typename unwrap_reference<T>::type unwrapped_self;
        BOOST_TEST((is_same<T,unwrapped_self>::value));

        cref_test(x, select<t_is_constant>());
    }
};

} // namespace unnamed

int test_main(int, char * [])
{
    wrapper<int>::test(1);
    wrapper<int const>::test(1);
    BOOST_TEST(!is_reference_wrapper<int>::value);
    BOOST_TEST(!is_reference_wrapper<int&>::value);
    BOOST_TEST(!is_reference_wrapper<int const>::value);
    BOOST_TEST(!is_reference_wrapper<int const&>::value);
    return 0;
}
