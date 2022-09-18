// Copyright 2022 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/core/detail/string_view.hpp>

int main()
{
    return boost::core::string_view( nullptr ).size() == 0;
}
