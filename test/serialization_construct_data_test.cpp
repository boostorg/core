// Copyright 2023 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#if defined(__clang__) && defined(__has_warning)
# if __has_warning( "-Wdeprecated-copy" )
#  pragma clang diagnostic ignored "-Wdeprecated-copy"
# endif
#endif

#include <boost/core/serialization.hpp>
#include <new>

struct X
{
    int v_;
    explicit X( int v ): v_( v ) {}

    template<class Ar> void serialize( Ar& /*ar*/, unsigned /*v*/ )
    {
    }
};

template<class Ar> void save_construct_data( Ar& ar, X const* t, unsigned /*v*/ )
{
    ar << t->v_;
}

template<class Ar> void load_construct_data( Ar& ar, X* t, unsigned /*v*/ )
{
    int v;
    ar >> v;

    ::new( t ) X( v );
}

struct Y
{
    X data_[ 2 ];

private:

    friend class boost::serialization::access;

    template<class Ar> void load( Ar& ar, unsigned v )
    {
        boost::core::load_construct_data_adl( ar, &data_[0], v );
        ar >> data_[0];

        boost::core::load_construct_data_adl( ar, &data_[1], v );
        ar >> data_[1];
    }

    template<class Ar> void save( Ar& ar, unsigned v ) const
    {
        boost::core::save_construct_data_adl( ar, &data_[0], v );
        ar << data_[0];

        boost::core::save_construct_data_adl( ar, &data_[1], v );
        ar << data_[1];
    }

    template<class Ar> void serialize( Ar& ar, unsigned v )
    {
        boost::core::split_member( ar, *this, v );
    }
};

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/core/lightweight_test.hpp>
#include <sstream>
#include <string>

int main()
{
    std::ostringstream os;

    Y y1 = {{ X(7), X(11) }};

    {
        boost::archive::text_oarchive ar( os );
        ar << y1;
    }

    std::string s = os.str();

    Y y2 = {{ X(0), X(0) }};

    {
        std::istringstream is( s );
        boost::archive::text_iarchive ar( is );
        ar >> y2;
    }

    BOOST_TEST_EQ( y1.data_[0].v_, y2.data_[0].v_ );
    BOOST_TEST_EQ( y1.data_[1].v_, y2.data_[1].v_ );

    return boost::report_errors();
}
