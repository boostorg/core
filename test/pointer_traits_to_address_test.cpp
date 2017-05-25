/*
Copyright 2017 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#include <boost/core/pointer_traits.hpp>
#include <boost/core/lightweight_test.hpp>

template<class T>
class pointer {
public:
    typedef typename boost::pointer_traits<T>::element_type element_type;
    pointer(T value)
        : value_(value) { }
    T operator->() const BOOST_NOEXCEPT {
        return value_;
    }
private:
    T value_;
};

int main()
{
    int i = 0;
    {
        typedef int* type;
        type p = &i;
        BOOST_TEST(boost::pointer_traits<type>::to_address(p) == &i);
    }
    {
        typedef pointer<int*> type;
        type p(&i);
        BOOST_TEST(boost::pointer_traits<type>::to_address(p) == &i);
    }
    {
        typedef pointer<pointer<int*> > type;
        type p(&i);
        BOOST_TEST(boost::pointer_traits<type>::to_address(p) == &i);
    }
    {
        typedef void* type;
        type p = &i;
        BOOST_TEST(boost::pointer_traits<type>::to_address(p) == &i);
    }
    {
        typedef pointer<void*> type;
        type p(&i);
        BOOST_TEST(boost::pointer_traits<type>::to_address(p) == &i);
    }
    {
        typedef const int* type;
        type p = &i;
        BOOST_TEST(boost::pointer_traits<type>::to_address(p) == &i);
    }
    {
        typedef pointer<const int*> type;
        type p(&i);
        BOOST_TEST(boost::pointer_traits<type>::to_address(p) == &i);
    }
    return boost::report_errors();
}
