#include <boost/core/lightweight_test.hpp>
#include <vector>

int main()
{
    BOOST_TEST(true);

    std::vector<int> v;
    std::vector<int>::iterator i = v.end();
    ++i;

    return boost::report_errors();
}
