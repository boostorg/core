//  Copyright 2023 Christian Mazakas
//  Distributed under the Boost Software License, Version 1.0.
//  https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_CORE_LATCH_HPP_INCLUDED
#define BOOST_CORE_LATCH_HPP_INCLUDED

#include <boost/config.hpp>

#if defined(BOOST_NO_CXX11_HDR_CONDITION_VARIABLE)
BOOST_PRAGMA_MESSAGE("boost::core::latch requires <condition_variable>")
#elif defined(BOOST_NO_CXX11_HDR_MUTEX)
BOOST_PRAGMA_MESSAGE("boost::core::latch requies <mutex>")
#else

#include <boost/assert.hpp>

#include <climits>
#include <condition_variable>
#include <cstddef>
#include <mutex>

namespace boost
{
namespace core
{
class latch
{
private:
    std::ptrdiff_t n_;
    mutable std::mutex m_;
    mutable std::condition_variable cv_;

public:
    explicit latch(std::ptrdiff_t expected) : n_{expected}, m_{}, cv_{}
    {
        BOOST_ASSERT(n_ >= 0);
        BOOST_ASSERT(n_ <= max());
    }

    latch(latch const &) = delete;
    latch &operator=(latch const &) = delete;

    ~latch() = default;

    void count_down(std::ptrdiff_t n = 1)
    {
        std::unique_lock<std::mutex> lk(m_);
        count_down_and_notify(lk, n);
    }

    bool try_wait() const noexcept
    {
        std::unique_lock<std::mutex> lk(m_);
        return is_ready();
    }

    void wait() const
    {
        std::unique_lock<std::mutex> lk(m_);
        wait_impl(lk);
    }

    void arrive_and_wait(std::ptrdiff_t n = 1)
    {
        std::unique_lock<std::mutex> lk(m_);
        bool should_wait = count_down_and_notify(lk, n);
        if (should_wait)
        {
            wait_impl(lk);
        }
    }

    static constexpr std::ptrdiff_t max() noexcept { return INT_MAX; }

private:
    bool is_ready() const { return n_ == 0; }

    bool count_down_and_notify(
        std::unique_lock<std::mutex> &lk, std::ptrdiff_t n)
    {
        n_ -= n;
        if (n_ == 0)
        {
            lk.unlock();
            cv_.notify_all();
            return false;
        }

        return true;
    }

    void wait_impl(std::unique_lock<std::mutex> &lk) const
    {
        cv_.wait(lk, [this]
                    { return this->is_ready(); });
    }
};
}
}

#endif

#endif // BOOST_CORE_LATCH_HPP_INCLUDED
