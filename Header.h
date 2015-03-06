//
//  Header.h
//  finalx
//
//  Created by Tyler Weimin Ouyang on 3/6/15.
//  Copyright (c) 2015 Golden. All rights reserved.
//

#ifndef finalx_Header_h
#define finalx_Header_h

struct graph { // A graph in compressed-adjacency-list (CSR) form
	int nv;            // number of vertices
	int ne;            // number of edges
	int *nbr;          // array of neighbors of all vertices
	int *firstnbr;     // index in nbr[] of first neighbor of each vtx
};

int read_edge_list (int **tailp, int **headp);
graph * graph_from_edge_list (int *tail, int* head, int nedges);
void print_CSR_graph (graph *G);

#endif