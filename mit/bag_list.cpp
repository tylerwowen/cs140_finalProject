// 6.884 Lab 4
// 
// Source file for a linked-list implementation of a bag.
// Copyright (c) 2010 TB Schardl and Jim Sukha
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

#ifndef BAG_LIST_CPP
#define BAG_LIST_CPP

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bag.h"

#include <list>


extern "C++" {
 
  template <typename T>
  class Bag<T, BAG_LIST> {    

  public:

    // Base case size for a list.
    static const size_t LIST_SPLIT_SIZE = 10;
    
    
    Bag<T, BAG_LIST>();    
    Bag<T, BAG_LIST>(Bag<T, BAG_LIST>*);
    ~Bag<T, BAG_LIST>();
    void insert(T);
    void merge(Bag<T, BAG_LIST>*);
    Bag<T, BAG_LIST>* split(void);
    
    inline bool can_split(void) const {
      return (this->bag->size() > this->my_split_size);
    }
    inline bool is_empty() const {
      return this->bag->empty();
    }

    inline int num_elements() const {
      return (int)this->bag->size();
    }

    void clear();      

    // Creates a new vector which contains of copy of all the
    // elements.
    typename std::vector<T>* copy_to_vector();
    
    // If you want to write your own iterator,
    // you can model it after the following methods. 
    typedef typename std::list<T>::iterator BaseIterator;
    BaseIterator begin();
    BaseIterator end();
    void advance(BaseIterator* it);
    const T& dereference(BaseIterator* it);

    inline void set_list_split_size(size_t base_size) {
      this->my_split_size = base_size;
    }
    
      
  private:
    std::list<T>* bag;
    unsigned int my_split_size;
  };

  

  //////////////////////////////
  ///                        ///
  /// Bag method definitions ///
  ///                        ///
  //////////////////////////////
  template <typename T>
  Bag<T, BAG_LIST>::Bag()
  {
    this->bag = new std::list<T>();
    this->my_split_size = LIST_SPLIT_SIZE;
    assert(this->bag->empty());
  }

  /*
   * Copy Constructor. Performs a shallow bag copy.
   * Useful for verifying Bag implementation correctness, since
   * the split method destroys the Bag.
   */
  template <typename T>
  Bag<T, BAG_LIST>::Bag(Bag<T, BAG_LIST> *that) {
    this->bag = that->bag;
  }


  template <typename T>
  Bag<T, BAG_LIST>::~Bag()
  {
    delete this->bag;
  }

  
  template <typename T>
  void
  Bag<T, BAG_LIST>::insert(T el) {
    this->bag->push_front(el);
  }

  template <typename T>
  void
  Bag<T, BAG_LIST>::merge(Bag<T, BAG_LIST>* that) {
    this->bag->merge(*that->bag);
    assert(that->bag->empty());
  }


  template <typename T>
  Bag<T, BAG_LIST>*
  Bag<T, BAG_LIST>::split() {
    size_t num_found = 0;
    Bag<T, BAG_LIST>* other_half = new Bag();


    if (0) {
      printf("Before split: this (%p) size = %lu, new (%p) = %lu\n",
	     this,
	     (long)this->bag->size(),
	     other_half,
	     (long)other_half->bag->size());
    }

    typename std::list<T>::iterator my_it;

    my_it= this->bag->begin();
    while ((my_it != this->bag->end()) && (num_found < this->my_split_size)) {
      my_it++;
      num_found++;
    }

    other_half->bag->splice(other_half->bag->begin(),
			    *this->bag,
			    this->bag->begin(),
			    my_it);

    if (0) {
      printf("After split: this (%p) size = %lu, new (%p) = %lu\n",
	     this,
	     (long)this->bag->size(),
	     other_half,
	     (long)other_half->bag->size());
    }    
    return other_half;    
  }

  template <typename T>
  void
  Bag<T, BAG_LIST>::clear(void) {
    this->bag->clear();
    assert(this->bag->empty());
  }



  template <typename T>
  typename std::vector<T>*
  Bag<T, BAG_LIST>::copy_to_vector() {

    std::vector<T>* vec = new std::vector<T>();
    assert(vec);
    
    typename std::list<T>::iterator it;
    for (it = this->bag->begin();
	 it != this->bag->end();
	 ++it) {
      vec->push_back(*it);
    }
    return vec;
  }

  template <typename T>
  typename Bag<T, BAG_LIST>::BaseIterator
  Bag<T, BAG_LIST>::begin() {
    return this->bag->begin();
  }
  template <typename T>
  typename Bag<T, BAG_LIST>::BaseIterator
  Bag<T, BAG_LIST>::end() {
    return this->bag->end();
  }
  template <typename T>
  void 
  Bag<T, BAG_LIST>::advance(typename Bag<T, BAG_LIST>::BaseIterator* it) {
    (*it)++;
  }
  template <typename T>
  const T&
  Bag<T, BAG_LIST>::dereference(typename Bag<T, BAG_LIST>::BaseIterator* it) {
    return **it;
  }
  
  
} // end of  extern "C++"



#endif
