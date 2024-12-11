#include <boost/array.hpp>
#include <boost/core/span.hpp>

// use boost::array as generic range since span has no special handling for it,
// unlike for std::array
int main()
{
    boost::array<int, 0> arr0{};
    boost::span<int, 0> sp0{arr0};
    boost::span<const int, 0> csp0{arr0};
    (void)sp0;
    (void)csp0;
    boost::array<int, 4> arr{};
    boost::span<int, 4> sp{arr};
    boost::span<const int, 4> csp{arr};
    (void)sp;
    (void)csp;
}
