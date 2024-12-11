#include <boost/array.hpp>
#include <boost/core/span.hpp>

int main()
{
    boost::array<int, 5> arr{};
    boost::span<int, 4> sp{arr};
    (void)sp;
}
