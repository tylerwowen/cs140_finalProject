// 6.884 Lab 4
//
// Graph representation header file
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

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <sys/types.h>
#include <time.h>

#include <cilk.h>
#include <cilk_mutex.h>

#include "bag.h"

// Infinite distance.
const unsigned int D_INFINITY = UINT_MAX;


class Graph
{

 private:
  // Number of nodes
  unsigned int nNodes;
  // Number of edges
  unsigned int nEdges;

  // Node and edge arrays.
  int * nodes;
  int * edges;

  
 public:
  // Constructor/Destructor
  Graph(const int nNodes, const int nEdges,
        std::vector<int>* edges[]);
  Graph(int *ir, int *jc, int m, int n, int nnz);
  ~Graph();

  // Accessors.
  inline unsigned int nodeCount() const {
    return nNodes;
  }
  inline unsigned int edgeCount() const {
    return nEdges;
  }

  // Various versions of BFS.
  // Each method takes in the index for the source,
  // and fills in the distance array for each node.
  

  // The serial BFS using a FIFO queue.
  int bfs_serial(const int s, unsigned int *distances);
  
  // TODO: Complete the two-queue version for part ()
  int bfs_2queue(const int s, unsigned int *distances);

  // A BFS implementation that uses a linked-list bag implementation.
  int bfs_bag_list(const int s, unsigned int *distances);
  
  // TODO: Implement your own bag data structure and use it for a
  // parallel BFS implementation.
  int bfs_parallel(const int s, unsigned int *distances);

  // TODO: Optimize your parallel BFS implementation.
  int bfs_parallel_opt(const int s, unsigned int *distances);
  

  // TODO: Test your implementation for memory-bandwidth issues.
  // extra_calls is a parameter by which you can inflate the
  // work of the computation.
  int bfs_memtest(const int s, unsigned int *distances, int extra_calls);

};

#endif
