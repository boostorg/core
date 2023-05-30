// Test for boost/core/bit.hpp (byteswap)
//
// Copyright 2023 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/core/bit.hpp>
#include <boost/core/lightweight_test.hpp>
#include <boost/cstdint.hpp>

int main()
{
    BOOST_TEST_EQ( boost::core::byteswap( (boost::int8_t)0x01 ), 0x01 );
    BOOST_TEST_EQ( boost::core::byteswap( (boost::uint8_t)0xF1 ), 0xF1 );

    BOOST_TEST_EQ( boost::core::byteswap( (boost::int16_t)0x0102 ), 0x0201 );
    BOOST_TEST_EQ( boost::core::byteswap( (boost::uint16_t)0xF1E2 ), 0xE2F1 );

    BOOST_TEST_EQ( boost::core::byteswap( (boost::int32_t)0x01020304 ), 0x04030201 );
    BOOST_TEST_EQ( boost::core::byteswap( (boost::uint32_t)0xF1E2D3C4u ), 0xC4D3E2F1u );

    BOOST_TEST_EQ( boost::core::byteswap( (boost::int64_t)0x0102030405060708ll ), 0x0807060504030201ll );
    BOOST_TEST_EQ( boost::core::byteswap( (boost::uint64_t)0xF1E2D3C4B5A69788ull ), 0x8897A6B5C4D3E2F1ull );

    return boost::report_errors();
}
