// Copyright (c) 2007 Joseph Gauterin
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/utility/swap.hpp>
#define BOOST_INCLUDE_MAIN
#include <boost/test/test_tools.hpp>

//Put test class in namespace other
namespace other
{
  #include "./swap_test_class.hpp"
}

//Provide swap function in namespace other
namespace other
{
  void swap(swap_test_class& left, swap_test_class& right)
  {
    left.swap(right);
  }
}

int test_main(int, char*[])
{
  other::swap_test_class object1;
  other::swap_test_class object2;
  boost::swap(object1,object2);

  BOOST_CHECK_EQUAL(other::swap_test_class::swap_count(),1);
  BOOST_CHECK_EQUAL(other::swap_test_class::copy_count(),0);

  return 0;
}

