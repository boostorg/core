module;

#include <cmath> // FP_xxx macros. Must be before import std to avoid conflicts
#include <stdio.h> // stderr. Must be before import std to avoid conflicts
#include <boost/core/detail/demangle_cxxabi.hpp> // must be before import std to avoid conflicts
#include <boost/core/detail/lwt_unattended.hpp>
#if defined(_MSC_VER)
#include <boost/core/detail/intrin.hpp>
#endif
#include <boost/core/alignof.hpp>
#include <boost/assert.hpp>
#include <boost/assert/source_location.hpp>
#include <boost/static_assert.hpp>
#include <boost/throw_exception.hpp>
#include <boost/config.hpp>
#include <boost/config/workaround.hpp>
#include <boost/current_function.hpp>
#include <boost/cstdint.hpp>

export module boost.core;

export import std; // re-exporting simplifies consuming lightweight_test

#define BOOST_CORE_INTERFACE_UNIT
#define BOOST_IN_MODULE_PURVIEW

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winclude-angled-in-module-purview"
#endif

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 5244)
#endif

#include <boost/core/detail/is_same.hpp>
#include <boost/core/detail/string_view.hpp>
#include <boost/core/detail/splitmix64.hpp>
#include <boost/core/demangle.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/core/lightweight_test.hpp>
#include <boost/core/lightweight_test_trait.hpp>
#include <boost/core/type_name.hpp>
#include <boost/core/bit.hpp>
#include <boost/core/addressof.hpp>
#include <boost/core/data.hpp>
#include <boost/core/size.hpp>
#include <boost/core/span.hpp>
#include <boost/core/make_span.hpp>
#include <boost/core/cmath.hpp>
#include <boost/core/checked_delete.hpp>
#include <boost/core/default_allocator.hpp>
#include <boost/core/exchange.hpp>
#include <boost/core/first_scalar.hpp>
#include <boost/core/functor.hpp>
#include <boost/core/identity.hpp>
#include <boost/core/ignore_unused.hpp>
#include <boost/core/launder.hpp>
#include <boost/core/max_align.hpp>
#include <boost/core/memory_resource.hpp>
#include <boost/core/noinit_adaptor.hpp>
#include <boost/core/noncopyable.hpp>
#include <boost/core/null_deleter.hpp>
#include <boost/core/fclose_deleter.hpp>
#include <boost/core/nvp.hpp>
#include <boost/core/pointer_in_range.hpp>
#include <boost/core/pointer_traits.hpp>
#include <boost/core/ref.hpp>
#include <boost/core/use_default.hpp>
#include <boost/core/verbose_terminate_handler.hpp>
#include <boost/core/allocator_access.hpp>
#include <boost/core/allocator_traits.hpp>
#include <boost/core/empty_value.hpp>
#include <boost/core/invoke_swap.hpp>
#include <boost/core/alloc_construct.hpp>
#include <boost/core/underlying_type.hpp>
#include <boost/is_placeholder.hpp>
#include <boost/non_type.hpp>
#include <boost/type.hpp>
#include <boost/visit_each.hpp>
#include <boost/get_pointer.hpp>
