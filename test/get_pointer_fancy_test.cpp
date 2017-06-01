/*
Copyright 2017 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#include <boost/get_pointer.hpp>
#include <boost/core/lightweight_test.hpp>

#if !defined(BOOST_NO_CXX11_ALLOCATOR)
template<class T>
class Fancy {
public:
    Fancy(T* value)
        : value_(value) { }

    T* operator->() const {
        return value_;
    }

private:
    T* value_;
};

template<class T>
class Fancier {
public:
    typedef typename std::pointer_traits<T>::element_type element_type;

    Fancier(T value)
        : value_(value) { }

    T operator->() const {
        return value_;
    }

private:
    T value_;
};

int main()
{
    int i = 0;
    Fancy<int> p(&i);
    BOOST_TEST(boost::get_pointer(p) == &i);
    Fancier<Fancy<int> > q(p);
    BOOST_TEST(boost::get_pointer(q) == &i);
    return boost::report_errors();
}
#else
int main()
{
    return 0;
}
#endif
