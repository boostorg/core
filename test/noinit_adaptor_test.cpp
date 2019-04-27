/*
Copyright 2019 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#include <boost/core/default_allocator.hpp>
#include <boost/core/noinit_adaptor.hpp>
#include <boost/core/lightweight_test.hpp>
#include <vector>

template<class T>
class creator
    : public boost::default_allocator<T> {
public:
    template<class U>
    struct rebind {
        typedef creator<U> other;
    };

    creator(int* count)
        : count_(count) { }

    template<class U>
    creator(const creator<U>& other)
        : count_(other.count()) { }

    template<class U, class V>
    void construct(U*, const V&) {
        ++(*count_);
    }

    template<class U>
    void destroy(U*) {
        --(*count_);
    }

    int* count() const {
        return count_;
    }

private:
    int* count_;
};

template<class T, class U>
inline bool
operator==(const creator<T>& lhs, const creator<U>& rhs)
{
    return lhs.count() == rhs.count();
}

template<class T, class U>
inline bool
operator!=(const creator<T>& lhs, const creator<U>& rhs)
{
    return !(lhs == rhs);
}

class type {
public:
    type() { }

    type(int value)
        : value_(value) { }

    int value() const {
        return value_;
    }

private:
    int value_;
};

int main()
{
    {
        int c = 0;
        std::vector<int, boost::noinit_adaptor<creator<int> > > v(&c);
        BOOST_TEST(c == 0);
        v.push_back(1);
        BOOST_TEST(v.front() == 1);
        v.push_back(2);
        BOOST_TEST(c == 0);
        v.clear();
        BOOST_TEST(c == 0);
        v.resize(5);
        BOOST_TEST(c == 0);
        v.front() = 1;
    }
    {
        int c = 0;
        std::vector<type, boost::noinit_adaptor<creator<type> > > v(&c);
        BOOST_TEST(c == 0);
        v.push_back(1);
        BOOST_TEST(v.front().value() == 1);
        v.push_back(2);
        BOOST_TEST(c == 0);
        v.clear();
        BOOST_TEST(c == 0);
        v.resize(5);
        BOOST_TEST(c == 0);
        v.front() = 1;
    }
    return boost::report_errors();
}
