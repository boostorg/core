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

#include <algorithm> //for std::copy and std::equal
#include <cstddef> //for std::size_t

//Provide swap function in both the namespace of swap_test_class
//(which is the global namespace), and the std namespace.
//It's common to provide a swap function for a class in both
//namespaces. Scott Meyers recommends doing so: Effective C++,
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

// Tests swapping 1-dimensional arrays.
void test_swapping_1D_arrays()
{
  const std::size_t dimension = 2;
  const swap_test_class initial_array1[dimension] = { swap_test_class(1), swap_test_class(2) };
  const swap_test_class initial_array2[dimension] = { swap_test_class(3), swap_test_class(4) };
  
  swap_test_class array1[dimension];
  swap_test_class array2[dimension];

  std::copy(initial_array1, initial_array1 + dimension, array1);
  std::copy(initial_array2, initial_array2 + dimension, array2);
  
  swap_test_class::reset();
  boost::swap(array1, array2);

  BOOST_CHECK(std::equal(array1, array1 + dimension, initial_array2));
  BOOST_CHECK(std::equal(array2, array2 + dimension, initial_array1));

  BOOST_CHECK_EQUAL(swap_test_class::swap_count(), dimension);
  BOOST_CHECK_EQUAL(swap_test_class::copy_count(), 0);
}


// Tests swapping 2-dimensional arrays.
void test_swapping_2D_arrays()
{
  const std::size_t first_dimension = 3;
  const std::size_t second_dimension = 4;
  const std::size_t number_of_elements = first_dimension * second_dimension;

  swap_test_class array1[first_dimension][second_dimension];
  swap_test_class array2[first_dimension][second_dimension];

  swap_test_class* const ptr1 = array1[0];
  swap_test_class* const ptr2 = array2[0];

  for (std::size_t i = 0; i < number_of_elements; ++i)
  {
    ptr1[i].set_data( static_cast<int>(i) );
    ptr2[i].set_data( static_cast<int>(i + number_of_elements) );
  }

  swap_test_class::reset();
  boost::swap(array1, array2);

  for (std::size_t i = 0; i < number_of_elements; ++i)
  {
    BOOST_CHECK_EQUAL(ptr1[i].get_data(), static_cast<int>(i + number_of_elements) );
    BOOST_CHECK_EQUAL(ptr2[i].get_data(), static_cast<int>(i) );
  }

  BOOST_CHECK_EQUAL(swap_test_class::swap_count(), number_of_elements);
  BOOST_CHECK_EQUAL(swap_test_class::copy_count(), 0);
}


int test_main(int, char*[])
{
  test_swapping_1D_arrays();
  test_swapping_2D_arrays();

  return 0;
}

