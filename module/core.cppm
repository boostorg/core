// Copyright (c) 2025 Antony Polukhin
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// To compile manually use a command like the folowing:
// clang++ -I ../include -std=c++20 --precompile -x c++-module core.cppm

#define BOOST_CORE_BEGIN_MODULE_EXPORT export {
#define BOOST_CORE_END_MODULE_EXPORT }

module;

#include <boost/config/header_deprecated.hpp>
#include <boost/config.hpp>
#include <boost/config/no_tr1/memory.hpp>
#include <boost/config/pragma_message.hpp>
#include <boost/config/workaround.hpp>

#include <boost/assert.hpp>
#include <boost/assert/source_location.hpp>

#include <boost/current_function.hpp>
#include <boost/static_assert.hpp>

#include <boost/throw_exception.hpp>  // TODO: modularize

#if (defined(__cpp_lib_uncaught_exceptions) && __cpp_lib_uncaught_exceptions >= 201411)
#if defined(__APPLE__)
#include <Availability.h>
#endif
#endif

#ifndef BOOST_CORE_HAS_STD_MODULE
#include <algorithm>
#include <array>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cxxabi.h>
#include <exception>
#include <functional>
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <iterator>
#include <limits>
#include <memory>
#include <new>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <typeinfo>
#include <type_traits>
#include <utility>
#include <wchar.h>
#endif

export module Boost.Core;

#ifdef BOOST_CORE_HAS_STD_MODULE
import std;
#endif

#ifdef __clang__
#   pragma clang diagnostic ignored "-Winclude-angled-in-module-purview"
#endif

#ifdef BOOST_CORE_ATTACH_TO_GLOBAL_MODULE
extern "C++" {
#include <boost/visit_each.hpp>
#include <boost/type.hpp>
#include <boost/get_pointer.hpp>
#include <boost/non_type.hpp>
#include <boost/ref.hpp>
#include <boost/core/bit.hpp>
#include <boost/core/ignore_unused.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/core/exchange.hpp>
#include <boost/core/pointer_in_range.hpp>
#include <boost/core/pointer_traits.hpp>
#include <boost/core/identity.hpp>
#include <boost/core/explicit_operator_bool.hpp>
#include <boost/core/allocator_access.hpp>
#include <boost/core/verbose_terminate_handler.hpp>
#include <boost/core/type_name.hpp>
#include <boost/core/invoke_swap.hpp>
#include <boost/core/uncaught_exceptions.hpp>
#include <boost/core/no_exceptions_support.hpp>
#include <boost/core/ref.hpp>
#include <boost/core/alloc_construct.hpp>
#include <boost/core/first_scalar.hpp>
#include <boost/core/lightweight_test_trait.hpp>
#include <boost/core/checked_delete.hpp>
#include <boost/core/alignof.hpp>
#include <boost/core/swap.hpp>
#include <boost/core/empty_value.hpp>
#include <boost/core/null_deleter.hpp>
#include <boost/core/data.hpp>
#include <boost/core/nvp.hpp>
#include <boost/core/snprintf.hpp>
#include <boost/core/demangle.hpp>
#include <boost/core/memory_resource.hpp>
#include <boost/core/default_allocator.hpp>
#include <boost/core/scoped_enum.hpp>
#include <boost/core/span.hpp>
#include <boost/core/lightweight_test.hpp>
#include <boost/core/is_same.hpp>
#include <boost/core/addressof.hpp>
#include <boost/core/launder.hpp>
#include <boost/core/noinit_adaptor.hpp>
#include <boost/core/allocator_traits.hpp>
#include <boost/core/serialization.hpp>
#include <boost/core/size.hpp>
#include <boost/core/fclose_deleter.hpp>
#include <boost/core/typeinfo.hpp>
#include <boost/core/quick_exit.hpp>
#include <boost/core/max_align.hpp>
#include <boost/core/underlying_type.hpp>
#include <boost/core/cmath.hpp>
#include <boost/core/noncopyable.hpp>
#include <boost/core/yield_primitives.hpp>
#include <boost/core/make_span.hpp>
#include <boost/core/use_default.hpp>
#include <boost/core/functor.hpp>
#include <boost/checked_delete.hpp>
#include <boost/swap.hpp>
#include <boost/iterator.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/utility/explicit_operator_bool.hpp>
#include <boost/utility/swap.hpp>
#include <boost/utility/addressof.hpp>
#include <boost/noncopyable.hpp>
}
#else
#include <boost/visit_each.hpp>
#include <boost/type.hpp>
#include <boost/get_pointer.hpp>
#include <boost/non_type.hpp>
#include <boost/ref.hpp>
#include <boost/core/bit.hpp>
#include <boost/core/ignore_unused.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/core/exchange.hpp>
#include <boost/core/pointer_in_range.hpp>
#include <boost/core/pointer_traits.hpp>
#include <boost/core/identity.hpp>
#include <boost/core/explicit_operator_bool.hpp>
#include <boost/core/allocator_access.hpp>
#include <boost/core/verbose_terminate_handler.hpp>
#include <boost/core/type_name.hpp>
#include <boost/core/invoke_swap.hpp>
#include <boost/core/uncaught_exceptions.hpp>
#include <boost/core/no_exceptions_support.hpp>
#include <boost/core/ref.hpp>
#include <boost/core/alloc_construct.hpp>
#include <boost/core/first_scalar.hpp>
#include <boost/core/lightweight_test_trait.hpp>
#include <boost/core/checked_delete.hpp>
#include <boost/core/alignof.hpp>
#include <boost/core/swap.hpp>
#include <boost/core/empty_value.hpp>
#include <boost/core/null_deleter.hpp>
#include <boost/core/data.hpp>
#include <boost/core/nvp.hpp>
#include <boost/core/snprintf.hpp>
#include <boost/core/demangle.hpp>
#include <boost/core/memory_resource.hpp>
#include <boost/core/default_allocator.hpp>
#include <boost/core/scoped_enum.hpp>
#include <boost/core/span.hpp>
#include <boost/core/lightweight_test.hpp>
#include <boost/core/is_same.hpp>
#include <boost/core/addressof.hpp>
#include <boost/core/launder.hpp>
#include <boost/core/noinit_adaptor.hpp>
#include <boost/core/allocator_traits.hpp>
#include <boost/core/serialization.hpp>
#include <boost/core/size.hpp>
#include <boost/core/fclose_deleter.hpp>
#include <boost/core/typeinfo.hpp>
#include <boost/core/quick_exit.hpp>
#include <boost/core/max_align.hpp>
#include <boost/core/underlying_type.hpp>
#include <boost/core/cmath.hpp>
#include <boost/core/noncopyable.hpp>
#include <boost/core/yield_primitives.hpp>
#include <boost/core/make_span.hpp>
#include <boost/core/use_default.hpp>
#include <boost/core/functor.hpp>
#include <boost/checked_delete.hpp>
#include <boost/swap.hpp>
#include <boost/iterator.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/utility/explicit_operator_bool.hpp>
#include <boost/utility/swap.hpp>
#include <boost/utility/addressof.hpp>
#include <boost/noncopyable.hpp>
#endif
