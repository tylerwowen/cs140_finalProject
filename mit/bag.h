// -*- C++ -*-
// 6.884 Lab 4
//
// Header file for Bag implementation
// Copyright (c) 2010 TB Schardl, Jim Sukha
//
/*
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef BAG_H
#define BAG_H

#include <cilk.h>

#include "bag_types.h"

	       
extern "C++" {

  // The generic class template for a Bag has no generic definition.
  // NOTE: THIS GENERIC CLASS NEVER GETS INSTANTIATED.
  //
  // These methods are only here for documentation purposes, that is,
  // these are methods which any bag implementation should implement
  // to work with the templates we have.

  template <typename T, BagType BType>
  class Bag
  {    
  public:
    Bag<T, BType>();
    Bag<T, BType>(Bag<T, BType>*);
    ~Bag<T, BType>();
    
    void insert(T);    
    bool is_empty() const;

    void merge(Bag<T, BType>*);    

    int num_elements() const;

    // Creates a new vector which contains of copy of all the
    // elements.
    typename std::vector<T>* copy_to_vector();



    // Returns true if the current bag can be split recursively.
    bool can_split() const;

    // Splits the current bag into two pieces (no particular
    // guarantees on the split)
    Bag<T, BType>* split(void);

    // Clears out the bag.
    void clear();

    // The type of this iterator should change, depending on the value
    // of BType.  We have put "void*" here for now just to have a
    // generic type.
    //
    // The idea is that once the bag has been split into sufficiently
    // small pieces, we would like to iterate over each indivisible
    // piece to access its elements.  For this task of iterating over
    // the "base case," we use an iterator.
    typedef void* BaseIterator;
    BaseIterator begin();
    BaseIterator end();
    void advance(BaseIterator* it);
    const T& dereference(BaseIterator* it);

    // Declarations needed so we can use this bag as reducer.
    friend class Bag_reducer<T, BType>;
    friend class cilk::monoid_base< Bag<T, BType> >;

  private:
    // This generic class template should never get instantiated.
  };

  
  // This is the implementation of the Bag reducer, based on the bag
  // template.  You should never have to worry about this part of the
  // bag implementation.
  template <typename T, BagType BType>
  class Bag_reducer
  {
  public:
    struct Monoid: cilk::monoid_base< Bag<T, BType> >
    {
      static void reduce (Bag<T, BType> *left,
			  Bag<T, BType> *right) {
	left->merge(right);
      }
    };
    
  private:
    cilk::reducer<Monoid> imp_;
    
  public:
    Bag_reducer();
    
    void insert(T);
    void merge(Bag_reducer<T, BType>*);

    Bag<T, BType>* split(void);    
    Bag<T, BType> &get_reference();
    
    bool is_empty() const;    
    void clear();
  };

  template <typename T, BagType BType>
  Bag_reducer<T, BType>::Bag_reducer() : imp_() { }
  
  template <typename T, BagType BType>
  void
  Bag_reducer<T, BType>::insert(T el)
  {
    imp_.view().insert(el);
  }

  template <typename T, BagType BType>
  void
  Bag_reducer<T, BType>::merge(Bag_reducer<T, BType>* that)
  {
    this->imp_.view().merge(that->imp_.view());
  }

  template <typename T, BagType BType>
  Bag<T, BType>*
  Bag_reducer<T, BType>::split(void)
  {
    return imp_.view().split();
  }

  template <typename T, BagType BType>
  Bag<T, BType>&
  Bag_reducer<T, BType>::get_reference()
  {
    return imp_.view();
  }

  template <typename T, BagType BType>
  bool
  Bag_reducer<T, BType>::is_empty() const
  {
    return imp_.view().is_empty();
  }  

  template <typename T, BagType BType>
  void
  Bag_reducer<T, BType>::clear() 
  {
    return imp_.view().clear();
  }

}  // End of extern "C++"



// Include any .cpp files for new bag implementations here.

#include "bag_list.cpp"
//#include "bag_parallel.cpp"
//#include "bag_opt.cpp"


#endif
