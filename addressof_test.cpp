// Copyright (C) 2002 Brad King (brad.king@kitware.com) 
//                    Douglas Gregor (gregod@cs.rpi.edu)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org

#define BOOST_INCLUDE_MAIN
#include <boost/test/test_tools.hpp>
#include <boost/utility.hpp>

struct useless_type {};

class nonaddressable {
public:
  void dummy(); // Silence GCC warning: all member of class are private

private:
  useless_type operator&() const;
};

int test_main(int, char*[])
{
  nonaddressable* px = new nonaddressable();

  nonaddressable& x = *px;
  BOOST_CHECK(boost::addressof(x) == px);

  const nonaddressable& cx = *px;
  BOOST_CHECK(boost::addressof(cx) == static_cast<const nonaddressable*>(px));

  volatile nonaddressable& vx = *px;
  BOOST_CHECK(boost::addressof(vx) == static_cast<volatile nonaddressable*>(px));

  const volatile nonaddressable& cvx = *px;
  BOOST_CHECK(boost::addressof(cvx) == static_cast<const volatile nonaddressable*>(px));
  
  return 0;
}
