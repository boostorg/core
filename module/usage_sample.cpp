//Copyright (c) 2025 Antony Polukhin.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// To compile manually use a command like the folowing:
// clang++ -std=c++20 -fmodule-file=core.pcm core.pcm usage_sample.cpp

import Boost.Core;

int main() {
    int x = 42;
    return *boost::core::launder(boost::addressof(x)) == 42 ? 0 : 1;
}
