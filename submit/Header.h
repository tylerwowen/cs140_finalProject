//
//  Header.h
//  finalx
//
//  Created by Tyler Weimin Ouyang on 3/6/15.
//  Copyright (c) 2015 Tyler Weimin Ouyang & Jenna Cryan. All rights reserved.
//

#ifndef finalx_Header_h
#define finalx_Header_h

#include <stdio.h>
#include <iostream>
#include "vertex.h"

struct graph { // A graph in compressed-adjacency-list (CSR) form
	int nv;            // number of vertices
	int ne;            // number of edges
	Vertex **vertices;  // array all vertices
	int *nbr;          // array of neighbors of all vertices
	int *firstnbr;     // index in nbr[] of first neighbor of each vtx
};

struct Node {
	int val_;
	Node* left_;
	Node* right_;
};

int read_edge_list (unsigned int **tailp, unsigned int **headp);
graph * graph_from_edge_list (unsigned int *tail, unsigned int* head, int nedges);
void print_CSR_graph (graph *G);
void bfs (int s, graph *G, int **levelp, int *nlevelsp, int **levelsizep, int **parentp);
int generateEdges(int SCALE, int edgefactor, unsigned int **head, unsigned int **tail);
#endif
