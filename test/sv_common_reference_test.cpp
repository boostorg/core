// Copyright 2021 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/core/detail/string_view.hpp>
#include <boost/core/lightweight_test_trait.hpp>
#include <boost/config/pragma_message.hpp>
#include <boost/config.hpp>
#include <string>

#if BOOST_CXX_VERSION < 202000L

BOOST_PRAGMA_MESSAGE( "Skipping test because BOOST_CXX_VERSION is " BOOST_STRINGIZE(BOOST_CXX_VERSION) )
int main() {}

#else

#include <version>

#if !defined(__cpp_lib_concepts)

BOOST_PRAGMA_MESSAGE( "Skipping test because __cpp_lib_concepts is not defined" )
int main() {}

#elif __cpp_lib_concepts < 201907L

BOOST_PRAGMA_MESSAGE( "Skipping test because __cpp_lib_concepts is " BOOST_STRINGIZE(__cpp_lib_concepts) )
int main() {}

#else

#include <type_traits>

using T = std::common_reference_t< boost::core::string_view&&, std::string& >;

static_assert( std::common_reference_with< boost::core::string_view&&, std::string& > );
static_assert( std::common_reference_with< boost::core::wstring_view&&, std::wstring const& > );

int main()
{
    BOOST_TEST_TRAIT_SAME( std::common_reference_t< boost::core::string_view&&, std::string& >, boost::core::string_view );
    BOOST_TEST_TRAIT_SAME( std::common_reference_t< boost::core::wstring_view&&, std::wstring const& >, boost::core::wstring_view );

    return boost::report_errors();
}

#endif
#endif
