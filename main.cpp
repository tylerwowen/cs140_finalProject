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
#include <sys/time.h>

double elapsed_seconds();

int main (int argc, char* argv[]) {
	graph *G;
	int *level, *levelsize, *parent;
	unsigned int *tail=NULL, *head=NULL;
	int nedges;
	int nlevels;
	int startvtx;
	int i, v, reached;
	double time;
	int scale;

	if (argc == 3) {
		startvtx = atoi (argv[1]);
		scale = atoi (argv[2]);
		nedges = generateEdges(scale, 16, &head, &tail);
	} 
	else if( argc == 2){
		startvtx = atoi (argv[1]);
		nedges = read_edge_list (&tail, &head);
	}
	else {
		printf("usage:   bfstest <startvtx> < <edgelistfile>\n");
		printf("example: cat sample.txt | ./bfstest 1\n");
		exit(1);
	}
	G = graph_from_edge_list (tail, head, nedges);
	free(tail);
	free(head);
	print_CSR_graph (G);

	printf("Starting vertex for BFS is %d.\n\n",startvtx);
	time = elapsed_seconds();
	bfs (startvtx, G, &level, &nlevels, &levelsize, &parent);
	time = elapsed_seconds()-time;
	printf("Sequential time is %fs\n",time);
	
	reached = 0;
	for (i = 0; i < nlevels; i++) reached += levelsize[i];
	printf("Breadth-first search from vertex %d reached %d levels and %d vertices.\n",
		   startvtx, nlevels, reached);
	for (i = 0; i < nlevels; i++) printf("level %d vertices: %d\n", i, levelsize[i]);
	if (G->nv < 20) {
		printf("\n  vertex parent  level\n");
		for (v = 1; v <= G->nv; v++) printf("%6d%7d%7d\n", v, parent[v], level[v]);
	}
	printf("\n");
	
	free(level);
	free(levelsize);
	free(parent);
	
	time = elapsed_seconds();
	pbfsList(G, G->vertices[startvtx], &level, &nlevels, &levelsize, &parent);
	time = elapsed_seconds()-time;
	printf("Parallel time is %fs\n",time);
	
	reached = 0;
	for (i = 0; i < nlevels; i++) reached += levelsize[i];
	printf("Parallel Breadth-first search from vertex %d reached %d levels and %d vertices.\n",
		   startvtx, nlevels, reached);
	for (i = 0; i < nlevels; i++) printf("level %d vertices: %d\n", i, levelsize[i]);
	if (G->nv < 20) {
		printf("\n  vertex parent  level\n");
		for (v = 1; v <= G->nv; v++) printf("%6d%7d%7d\n", v, parent[v], level[v]);
	}
	printf("\n");
}
