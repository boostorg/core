#include <boost/array.hpp>
#include <boost/core/span.hpp>

int main()
{
    boost::array<int, 3> arr{};
    boost::span<int, 4> sp{arr};
    (void)sp;
}
