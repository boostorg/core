#include <boost/core/span.hpp>
#include <boost/static_assert.hpp>
#include <thread>
#include <type_traits>
#include <vector>
#if __cplusplus >= 202302L
#include <span>
#endif
using namespace boost;

// well known trick to make size() nicer.
struct MyArray3 {
    static constexpr std::integral_constant<std::size_t, 3> size{};
};

// tests for helper used in span range constructor
int main()
{
    constexpr auto vec_size = detail::span_default_constructed_size<std::vector<int>>();
    BOOST_STATIC_ASSERT(vec_size == 0);
    constexpr auto str_size = detail::span_default_constructed_size<std::string>();
    BOOST_STATIC_ASSERT(str_size == 0);
    constexpr auto arr0_size = detail::span_default_constructed_size<std::array<int, 0>>();
    BOOST_STATIC_ASSERT(arr0_size == 0);
    constexpr auto arr1_size = detail::span_default_constructed_size<std::array<int, 1>>();
    BOOST_STATIC_ASSERT(arr1_size == 1);
    constexpr auto arr2_size = detail::span_default_constructed_size<std::array<int, 2>>();
    BOOST_STATIC_ASSERT(arr2_size == 2);
    constexpr auto non_constexpr_element_arr_size = detail::span_default_constructed_size<std::array<std::thread, 2>>();
    BOOST_STATIC_ASSERT(non_constexpr_element_arr_size == 0);

    constexpr auto const_arr0_size = detail::span_default_constructed_size<const std::array<int, 0>>();
    BOOST_STATIC_ASSERT(const_arr0_size == 0);
    constexpr auto const_arr2_size = detail::span_default_constructed_size<const std::array<int, 2>>();
    BOOST_STATIC_ASSERT(const_arr2_size == 2);

#ifdef __cpp_lib_integral_constant_callable
    constexpr auto my_array3_size = detail::span_default_constructed_size<MyArray3>();
    BOOST_STATIC_ASSERT(my_array3_size == 3);
#endif

#if __cplusplus >= 202302L
    // static extent span has no default constructor so we can not determine size
    constexpr auto span0_size = detail::span_default_constructed_size<std::span<int, 0>>();
    BOOST_STATIC_ASSERT(span0_size == 0);
    constexpr auto span1_size = detail::span_default_constructed_size<std::span<int, 1>>();
    BOOST_STATIC_ASSERT(span1_size == 0);
    constexpr auto span2_size = detail::span_default_constructed_size<std::span<int, 2>>();
    BOOST_STATIC_ASSERT(span2_size == 0);

    constexpr auto const_span2_size = detail::span_default_constructed_size<std::span<const int, 2>>();
    BOOST_STATIC_ASSERT(const_span2_size == 0);

    constexpr auto dyn_span_size = detail::span_default_constructed_size<std::span<int>>();
    BOOST_STATIC_ASSERT(dyn_span_size == 0);
#endif
}
