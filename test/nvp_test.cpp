/*
Copyright 2019 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#include <boost/core/nvp.hpp>
#include <boost/core/lightweight_test_trait.hpp>

class saver {
public:
    struct is_saving {
        static const bool value = true;
    };

    explicit saver(int value)
        : value_(value) { }

    int get() const {
        return value_;
    }

    void operator<<(int value) {
        value_ = value;
    }

private:
    int value_;
};

class loader {
public:
    struct is_saving {
        static const bool value = false;
    };

    explicit loader(int value)
        : value_(value) { }

    void operator>>(int& value) {
        value = value_;
    }

private:
    int value_;
};

void test()
{
    const char* n = "name";
    int v = 1;
    boost::nvp<int> p(n, v);
    BOOST_TEST_EQ(p.name(), n);
    BOOST_TEST_EQ(p.value(), 1);
    BOOST_TEST_EQ(&p.value(), &v);
}

void test_save()
{
    int v = 1;
    boost::nvp<int> p("name", v);
    saver s(0);
    p.save(s, unsigned());
    BOOST_TEST_EQ(s.get(), 1);
}

void test_load()
{
    int v = 1;
    boost::nvp<int> p("name", v);
    loader l(5);
    p.load(l, unsigned());
    BOOST_TEST_EQ(p.value(), 5);
}

void test_serialize()
{
    int v = 1;
    boost::nvp<int> p("name", v);
    saver s(0);
    p.serialize(s, unsigned());
    BOOST_TEST_EQ(s.get(), 1);
}

void test_deserialize()
{
    int v = 1;
    boost::nvp<int> p("name", v);
    loader l(5);
    p.serialize(l, unsigned());
    BOOST_TEST_EQ(p.value(), 5);
}

void test_trait()
{
    BOOST_TEST_TRAIT_TRUE((boost::is_nvp<boost::nvp<int> >));
    BOOST_TEST_TRAIT_FALSE((boost::is_nvp<int>));
    BOOST_TEST_TRAIT_TRUE((boost::is_nvp<const boost::nvp<int> >));
    BOOST_TEST_TRAIT_FALSE((boost::is_nvp<const int>));
    BOOST_TEST_TRAIT_TRUE((boost::is_nvp<volatile boost::nvp<int> >));
    BOOST_TEST_TRAIT_FALSE((boost::is_nvp<volatile int>));
    BOOST_TEST_TRAIT_TRUE((boost::is_nvp<const volatile boost::nvp<int> >));
    BOOST_TEST_TRAIT_FALSE((boost::is_nvp<const volatile int>));
}

void test_factory()
{
    const char* n = "name";
    int v = 1;
    boost::nvp<int> p = boost::make_nvp(n, v);
    BOOST_TEST_EQ(p.name(), n);
    BOOST_TEST_EQ(p.value(), 1);
    BOOST_TEST_EQ(&p.value(), &v);
}

int main()
{
    test();
    test_save();
    test_load();
    test_serialize();
    test_deserialize();
    test_trait();
    test_factory();
    return boost::report_errors();
}
