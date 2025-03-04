#include <boost/array.hpp>
#include <boost/core/span.hpp>
#if __cplusplus >= 202302L
#include <span>
#endif
#include <vector>

int main()
{
    // many cases where constexpr default constructed container has 0 size, including C++20 onwards
    // std::vector so we can not catch that case.
    {
        boost::array<int, 0> arr{};
        boost::span<int, 4> sp{arr};
        (void)sp;
        std::vector<int> vec(10, 10);
        boost::span<int, 4> sp2{vec};
        (void)sp2;
    }

#if __cplusplus >= 202302L
    // fixed extent std::span does not have default constructor so we can not get size
    {
        std::array<int, 4> arr{};
        std::span<int, 4> std_sp{arr};
        boost::span<int, 3> sp{std_sp};
        (void)sp;
    }
    // no size check possible for dynamic extent std::span
    {
        std::array<int, 4> arr{};
        std::span<int> std_sp{arr};
        boost::span<int, 3> sp{std_sp};
        (void)sp;
    }
#endif
}
