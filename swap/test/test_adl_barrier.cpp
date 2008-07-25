// Copyright (c) 2008 Joseph Gauterin, Niels Dekker
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// boost::swap internally does an unqualified function call to swap.
// This could have led to ambiguity or infinite recursion, when the
// objects to be swapped would themselves be from the boost namespace.
// If so, boost::swap itself might be found by argument dependent lookup
// (ADL). The implementation of boost::swap resolves this issue by
// using a barrier namespace. The following test checks this "ADL barrier".

#include <boost/utility/swap.hpp>
#define BOOST_INCLUDE_MAIN
#include <boost/test/test_tools.hpp>

//Put test class in namespace boost
namespace boost
{
  #include "./swap_test_class.hpp"
}


int test_main(int, char*[])
{
  boost::swap_test_class object1;
  boost::swap_test_class object2;
  boost::swap(object1,object2);

  BOOST_CHECK_EQUAL(boost::swap_test_class::swap_count(),0);
  BOOST_CHECK_EQUAL(boost::swap_test_class::copy_count(),3);

  return 0;
}

