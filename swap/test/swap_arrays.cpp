// Copyright (c) 2008 Joseph Gauterin, Niels Dekker
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/utility/swap.hpp>
#define BOOST_INCLUDE_MAIN
#include <boost/test/test_tools.hpp>

//Put test class in the global namespace
#include "./swap_test_class.hpp"

//Provide swap function in both the namespace of swap_test_class
//(which is the global namespace), and the std namespace.
//It's common to provide a swap function for a class in both
//namespaces. Scott Meyers recommends doing so: Effectice C++,
//Third Edition, item 25, "Consider support for a non-throwing swap".
void swap(swap_test_class& left, swap_test_class& right)
{
  left.swap(right);
}

namespace std
{
  template <>
  void swap(swap_test_class& left, swap_test_class& right)
  {
    left.swap(right);
  }
}


int test_main(int, char*[])
{
  const std::size_t dimension = 7;

  swap_test_class array1[dimension];
  swap_test_class array2[dimension];
  boost::swap(array1, array2);

  BOOST_CHECK_EQUAL(swap_test_class::swap_count(), dimension);
  BOOST_CHECK_EQUAL(swap_test_class::copy_count(), 0);

  swap_test_class::reset();

  const std::size_t firstDimension = 3;
  const std::size_t secondDimension = 4;

  swap_test_class two_d_array1[firstDimension][secondDimension];
  swap_test_class two_d_array2[firstDimension][secondDimension];
  boost::swap(two_d_array1, two_d_array2);

  BOOST_CHECK_EQUAL(swap_test_class::swap_count(), firstDimension*secondDimension);
  BOOST_CHECK_EQUAL(swap_test_class::copy_count(), 0);

  return 0;
}

