//  Copyright 2023 Christian Mazakas
//  Distributed under the Boost Software License, Version 1.0.
//  https://www.boost.org/LICENSE_1_0.txt

#include <boost/config.hpp>
#include <boost/config/pragma_message.hpp>

#if !defined(BOOST_NO_CXX11_HDR_CONDITION_VARIABLE) && !defined(BOOST_NO_CXX11_HDR_MUTEX)

#define BOOST_ENABLE_ASSERT_HANDLER

#include <boost/core/latch.hpp>

#include <boost/core/lightweight_test.hpp>

#include <thread>
#include <vector>

struct exception
{
};

namespace boost
{
    void assertion_failed(
        char const *expr, char const *function, char const *file, long line)
    {
        (void)expr;
        (void)function;
        (void)file;
        (void)line;
        throw exception{};
    }
} // namespace boost

namespace
{
    void test_max() { BOOST_TEST_EQ(boost::core::latch::max(), INT_MAX); }

    void test_constructor()
    {
        {
            auto const f = []
            {
                boost::core::latch l(-1);
                (void)l;
            };
            BOOST_TEST_THROWS(f(), exception);
        }

        {
            std::ptrdiff_t n = 0;

            boost::core::latch l(n);
            BOOST_TEST(l.try_wait());
        }

        {
            std::ptrdiff_t n = 16;

            boost::core::latch l(n);
            BOOST_TEST_NOT(l.try_wait());

            l.count_down(16);
            BOOST_TEST(l.try_wait());
        }

#if PTRDIFF_MAX > INT_MAX
        {
            auto const f = []
            {
                std::ptrdiff_t n = INT_MAX;
                n += 10;
                boost::core::latch l(n);
                (void)l;
            };
            BOOST_TEST_THROWS(f(), exception);
        }
#endif
    }

    void test_count_down_and_wait()
    {
        constexpr std::ptrdiff_t n = 1024;

        boost::core::latch l(2 * n);

        bool bs[] = {false, false};

        std::thread t1([&]
                       {
      l.wait();
      BOOST_TEST(bs[0]);
      BOOST_TEST(bs[1]); });

        std::thread t2([&]
                       {
      for (int i = 0; i < n; ++i) {
        if (i == (n - 1)) {
          bs[0] = true;
        } else {
          BOOST_TEST_NOT(l.try_wait());
        }

        l.count_down(1);
      } });

        for (int i = 0; i < n; ++i)
        {
            if (i == (n - 1))
            {
                bs[1] = true;
            }
            else
            {
                BOOST_TEST_NOT(l.try_wait());
            }

            l.count_down(1);
        }

        t1.join();
        t2.join();

        BOOST_TEST(l.try_wait());
    }

    void test_arrive_and_wait()
    {
        constexpr std::ptrdiff_t n = 16;

        boost::core::latch l(2 * n);

        int xs[n] = {0};

        std::vector<std::thread> threads;
        for (int i = 0; i < n; ++i)
        {
            threads.emplace_back([&l, &xs, i]
                                 {
        for (int j = 0; j < n; ++j) {
          BOOST_TEST_EQ(xs[j], 0);
        }

        l.arrive_and_wait(2);

        xs[i] = 1; });
        }

        for (auto &t : threads)
        {
            t.join();
        }

        for (int i = 0; i < n; ++i)
        {
            BOOST_TEST_EQ(xs[i], 1);
        }
    }
} // namespace

int main()
{
    test_max();
    test_constructor();
    test_count_down_and_wait();
    test_arrive_and_wait();

    return boost::report_errors();
}

#else

BOOST_PRAGMA_MESSAGE("latch_test requires <mutex>, <condition_variable>")

int main() { return 0; }

#endif
