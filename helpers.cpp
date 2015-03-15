//
//  helpers.cpp
//  finalx
//
//  Created by Tyler Weimin Ouyang on 3/6/15.
//  Copyright (c) 2015 Tyler Weimin Ouyang & Jenna Cryan. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

int read_edge_list (int **tailp, int **headp) {
	int max_edges = 1000000;
	int nedges, nr, t, h;
	*tailp = (int *) calloc(max_edges, sizeof(int));
	*headp = (int *) calloc(max_edges, sizeof(int));
	nedges = 0;
	nr = scanf("%i %i",&t,&h);
	while (nr == 2) {
		if (nedges >= max_edges) {
			printf("Limit of %d edges exceeded.\n",max_edges);
			exit(1);
		}
		(*tailp)[nedges] = t;
		(*headp)[nedges++] = h;
		nr = scanf("%i %i",&t,&h);
	}
	return nedges;
}


graph * graph_from_edge_list (int *tail, int* head, int nedges) {
	graph *G;
	int i, e, v, maxv;
	G = (graph *) calloc(1, sizeof(graph));
	G->ne = nedges;
	maxv = 0;

	// count vertices
	for (e = 0; e < G->ne; e++) {
		if (tail[e] > maxv) maxv = tail[e];
		if (head[e] > maxv) maxv = head[e];
	}
	G->nv = maxv+1;
	G->nbr = (int *) calloc(G->ne, sizeof(int));
	G->firstnbr = (int *) calloc(G->nv+1, sizeof(int));
	G->dist = (unsigned int *) calloc(G->nv+1, sizeof(unsigned int));

	// count neighbors of vertex v in firstnbr[v+1],
	for (e = 0; e < G->ne; e++) G->firstnbr[tail[e]+1]++;

	// cumulative sum of neighbors gives firstnbr[] values
	for (v = 0; v < G->nv; v++) G->firstnbr[v+1] += G->firstnbr[v];

	// initialize dist with unsigned 0-1
	for (v = 0; v < G->nv; v++) G->dist[v+1]--;
	
	// pass through edges, slotting each one into the CSR structure
	for (e = 0; e < G->ne; e++) {
		i = G->firstnbr[tail[e]]++;
		G->nbr[i] = head[e];
	}
	// the loop above shifted firstnbr[] left; shift it back right
	for (v = G->nv; v > 0; v--) G->firstnbr[v] = G->firstnbr[v-1];
	G->firstnbr[0] = 0;
	return G;
}


void print_CSR_graph (graph *G) {
	int vlimit = 20;
	int elimit = 50;
	int e,v;
	printf("\nGraph has %d vertices and %d edges.\n",G->nv,G->ne);
	printf("firstnbr =");
	if (G->nv < vlimit) vlimit = G->nv;
	for (v = 0; v <= vlimit; v++) printf(" %d",G->firstnbr[v]);
	if (G->nv > vlimit) printf(" ...");
	printf("\n");
	printf("nbr =");
	if (G->ne < elimit) elimit = G->ne;
	for (e = 0; e < elimit; e++) printf(" %d",G->nbr[e]);
	if (G->ne > elimit) printf(" ...");
	printf("\n\n");
}
