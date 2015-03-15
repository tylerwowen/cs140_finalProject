// -*- C++ -*-
// 6.884 Lab 4
// Source file for Bag implementation
//
// Copyright (c) 2010 <INSERT YOUR NAME>

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

#ifndef BAG_OPT_CPP
#define BAG_OPT_CPP

#include "bag.h"

// TODO: You'll want to implement a pennant type off of which you can
// implement the bag.

extern "C++" {
  template <typename T>
  class Bag<T, BAG_OPT> {

  public:

    // The common methods for the bag interface.
    Bag<T, BAG_OPT>();
    Bag<T, BAG_OPT>(Bag<T, BAG_OPT>*);
    ~Bag<T, BAG_OPT>();  
    void insert(T);   
    void merge(Bag<T, BAG_OPT>*);   
    Bag<T, BAG_OPT>* split(void);
    
    bool is_empty() const;

    int num_elements() const;
    
    void clear();

    // Jim: All these remaining methods are not filled in yet.

    bool can_split(void) const;

    // Creates a new vector which contains of copy of all the
    // elements.
    typename std::vector<T>* copy_to_vector() const;

    // TODO: Choose a type for your BaseIterator
    //typedef ???? BaseIterator;
    BaseIterator begin();
    BaseIterator end();
    void advance(BaseIterator* it);
    const T& dereference(BaseIterator* it);

  private:
    // Member variables for the bag implementation.
    // TODO: Fill this in
  };
}

// TODO: Implement the bag.

#endif
