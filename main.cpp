//
//  main.cpp
//  finalx
//
//  Created by Tyler Weimin Ouyang on 3/6/15.
//  Copyright (c) 2015 Tyler Weimin Ouyang & Jenna Cryan. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "Header.h"
#include "pbfs.h"

int main (int argc, char* argv[]) {
	graph *G;
	int *level, *levelsize, *parent;
	int *tail, *head;
	int nedges;
	int nlevels;
	int startvtx;
	int i, v, reached;

	if (argc == 2) {
		startvtx = atoi (argv[1]);
	} else {
		printf("usage:   bfstest <startvtx> < <edgelistfile>\n");
		printf("example: cat sample.txt | ./bfstest 1\n");
		exit(1);
	}
	nedges = read_edge_list (&tail, &head);
	G = graph_from_edge_list (tail, head, nedges);
	free(tail);
	free(head);
	print_CSR_graph (G);

	printf("Starting vertex for BFS is %d.\n\n",startvtx);
	bfs (startvtx, G, &level, &nlevels, &levelsize, &parent);
	
	
	reached = 0;
	for (i = 0; i < nlevels; i++) reached += levelsize[i];
	printf("Breadth-first search from vertex %d reached %d levels and %d vertices.\n",
		   startvtx, nlevels, reached);
	for (i = 0; i < nlevels; i++) printf("level %d vertices: %d\n", i, levelsize[i]);
	if (G->nv < 20) {
		printf("\n  vertex parent  level\n");
		for (v = 0; v < G->nv; v++) printf("%6d%7d%7d\n", v, parent[v], level[v]);
	}
	printf("\n");
	
	free(level);
	free(levelsize);
	free(parent);
	
	pbfsList(G, G->vertices[startvtx], &level, &nlevels, &levelsize, &parent);
	reached = 0;
	for (i = 0; i < nlevels; i++) reached += levelsize[i];
	printf("Parallel Breadth-first search from vertex %d reached %d levels and %d vertices.\n",
		   startvtx, nlevels, reached);
	for (i = 0; i < nlevels; i++) printf("level %d vertices: %d\n", i, levelsize[i]);
	if (G->nv < 20) {
		printf("\n  vertex parent  level\n");
		for (v = 0; v < G->nv; v++) printf("%6d%7d%7d\n", v, parent[v], level[v]);
	}
	printf("\n");
}
