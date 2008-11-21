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

template <class T>
class swap_test_template
{
public:
  swap_test_class swap_test_object;
};

template <class T>
inline bool operator==(const swap_test_template<T> & lhs, const swap_test_template<T> & rhs)
{
  return lhs.swap_test_object == rhs.swap_test_object;
}

template <class T>
inline bool operator!=(const swap_test_template<T> & lhs, const swap_test_template<T> & rhs)
{
  return !(lhs == rhs);
}

//Provide swap function in the namespace of swap_test_template
//(which is the global namespace).  Note that it isn't allowed to put
//an overload of this function within the std namespace.
template <class T>
void swap(swap_test_template<T>& left, swap_test_template<T>& right)
{
  left.swap_test_object.swap(right.swap_test_object);
}


int test_main(int, char*[])
{
  const std::size_t dimension = 2;
  const swap_test_template<int> initial_array1[dimension] = { swap_test_class(1), swap_test_class(2) };
  const swap_test_template<int> initial_array2[dimension] = { swap_test_class(3), swap_test_class(4) };
  
  swap_test_template<int> array1[dimension];
  swap_test_template<int> array2[dimension];

  std::copy(initial_array1, initial_array1 + dimension, array1);
  std::copy(initial_array2, initial_array2 + dimension, array2);
  
  swap_test_class::reset();
  boost::swap(array1, array2);

  BOOST_CHECK(std::equal(array1, array1 + dimension, initial_array2));
  BOOST_CHECK(std::equal(array2, array2 + dimension, initial_array1));

  BOOST_CHECK_EQUAL(swap_test_class::swap_count(), dimension);
  BOOST_CHECK_EQUAL(swap_test_class::copy_count(), 0);

  return 0;
}
