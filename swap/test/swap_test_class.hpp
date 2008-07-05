// Copyright (c) 2007 Joseph Gauterin
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Tests that the swap header compiles as a standalone translation unit

#ifndef BOOST_UTILITY_SWAP_TEST_CLASS_HPP
#define BOOST_UTILITY_SWAP_TEST_CLASS_HPP


class swap_test_class
{
public:
  swap_test_class()
  {
    ++constructCount();
  }

  ~swap_test_class()
  {
    ++destructCount();
  }

  swap_test_class(const swap_test_class&)
  {
    ++copyCount();
    ++destructCount();
  }

  swap_test_class& operator=(const swap_test_class&)
  {
    ++copyCount();
    return *this;
  }

  void swap(swap_test_class& other)
  {
    ++swapCount();
  }


  static unsigned int swap_count(){ return swapCount(); }
  static unsigned int copy_count(){ return copyCount(); }
  static unsigned int construct_count(){ return constructCount(); }
  static unsigned int destruct_count(){ return destructCount(); }

  static void reset()
  {
    swapCount() = 0;
    copyCount() = 0;    
    constructCount() = 0;
    destructCount() = 0;
  }

private:
  static unsigned int& swapCount()
  {
    static unsigned int value = 0;
    return value;
  }

  static unsigned int& copyCount()    
  {
    static unsigned int value = 0;
    return value;
  }

  static unsigned int& constructCount()    
  {
    static unsigned int value = 0;
    return value;
  }

  static unsigned int& destructCount()    
  {
    static unsigned int value = 0;
    return value;
  }

};

#endif

// Copyright (c) 2007 Joseph Gauterin
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Tests that the swap header compiles as a standalone translation unit

#ifndef BOOST_UTILITY_SWAP_TEST_CLASS_HPP
#define BOOST_UTILITY_SWAP_TEST_CLASS_HPP


class swap_test_class
{
public:
  swap_test_class()
  {
    ++constructCount();
  }

  ~swap_test_class()
  {
    ++destructCount();
  }

  swap_test_class(const swap_test_class&)
  {
    ++copyCount();
    ++destructCount();
  }

  swap_test_class& operator=(const swap_test_class&)
  {
    ++copyCount();
    return *this;
  }

  void swap(swap_test_class& other)
  {
    ++swapCount();
  }


  static unsigned int swap_count(){ return swapCount(); }
  static unsigned int copy_count(){ return copyCount(); }
  static unsigned int construct_count(){ return constructCount(); }
  static unsigned int destruct_count(){ return destructCount(); }

  static void reset()
  {
    swapCount() = 0;
    copyCount() = 0;    
    constructCount() = 0;
    destructCount() = 0;
  }

private:
  static unsigned int& swapCount()
  {
    static unsigned int value = 0;
    return value;
  }

  static unsigned int& copyCount()    
  {
    static unsigned int value = 0;
    return value;
  }

  static unsigned int& constructCount()    
  {
    static unsigned int value = 0;
    return value;
  }

  static unsigned int& destructCount()    
  {
    static unsigned int value = 0;
    return value;
  }

};

#endif


