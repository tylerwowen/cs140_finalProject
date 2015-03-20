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

int read_edge_list (unsigned int **tailp, unsigned int **headp) {
	unsigned int max_edges = 1000000;
	unsigned int nedges, nr, t, h;
	*tailp = (unsigned int *) calloc(max_edges, sizeof(unsigned int));
	*headp = (unsigned int *) calloc(max_edges, sizeof(unsigned int));
	nedges = 0;
	nr = scanf("%u %u",&t,&h);
	while (nr == 2) {
		if (nedges >= max_edges) {
			printf("Limit of %d edges exceeded.\n",max_edges);
			exit(1);
		}
		(*tailp)[nedges] = t;
		(*headp)[nedges++] = h;
		nr = scanf("%u %u",&t,&h);
	}
	return nedges;
}


graph * graph_from_edge_list (unsigned int *tail, unsigned int* head, int nedges) {
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

	// count neighbors of vertex v in firstnbr[v+1],
	for (e = 0; e < G->ne; e++) G->firstnbr[tail[e]+1]++;

	// cumulative sum of neighbors gives firstnbr[] values
	for (v = 0; v < G->nv; v++) G->firstnbr[v+1] += G->firstnbr[v];
	
	// pass through edges, slotting each one into the CSR structure
	for (e = 0; e < G->ne; e++) {
		i = G->firstnbr[tail[e]]++;
		G->nbr[i] = head[e];
	}
	
	// the loop above shifted firstnbr[] left; shift it back right
	for (v = G->nv; v > 0; v--) G->firstnbr[v] = G->firstnbr[v-1];
	G->firstnbr[0] = 0;
	
	// initialize vertices
	G->vertices = new Vertex*[G->nv+1];
	for (v = 0; v < G->nv - 1; v++) {
		G->vertices[v] = new Vertex(v, G->firstnbr[v+1] - G->firstnbr[v]);
	}
	G->vertices[v] = new Vertex(v, G->ne - G->firstnbr[v]);
	for (v = 0; v < G->nv - 1; v++) {
		e = 0;
		for (i = G->firstnbr[v]; i < G->firstnbr[v+1]; i++) {
			G->vertices[v]->addNeighbor(G->vertices[G->nbr[i]], e++);
		}
	}
	e = 0;
	for (i = G->firstnbr[v]; i < G->ne; i++) {
		G->vertices[v]->addNeighbor(G->vertices[G->nbr[i]], e++);
	}
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
#if DEBUG==1	
	for (int i=0; i<G->nv; i++) {
		printf("vertex %d's neighbors: ", i);
		for (int j=0; j<G->vertices[i]->getNumOfAdjacency(); j++) {
			printf("%d ",G->vertices[i]->getNthAdjacency(j)->getVertexNum());
		}
		printf("\n");
	}
#endif
}

void bfs (int s, graph *G, int **levelp, int *nlevelsp,
		  int **levelsizep, int **parentp) {
	int *level, *levelsize, *parent;
	int thislevel;
	int *queue, back, front;
	int i, v, w, e;
	level = *levelp = (int *) calloc(G->nv, sizeof(int));
	levelsize = *levelsizep = (int *) calloc(G->nv, sizeof(int));
	parent = *parentp = (int *) calloc(G->nv, sizeof(int));
	queue = (int *) calloc(G->nv, sizeof(int));
	
	// initially, queue is empty, all levels and parents are -1
	back = 0;   // position next element will be added to queue
	front = 0;  // position next element will be removed from queue
	for (v = 0; v < G->nv; v++) level[v] = -1;
	for (v = 0; v < G->nv; v++) parent[v] = -1;
	
	// assign the starting vertex level 0 and put it on the queue to explore
	thislevel = 0;
	level[s] = 0;
	levelsize[0] = 1;
	queue[back++] = s;
	
	// loop over levels, then over vertices at this level, then over neighbors
	while (levelsize[thislevel] > 0) {
		levelsize[thislevel+1] = 0;
		for (i = 0; i < levelsize[thislevel]; i++) {
			v = queue[front++];       // v is the current vertex to explore from
			for (e = G->firstnbr[v]; e < G->firstnbr[v+1]; e++) {
				w = G->nbr[e];          // w is the current neighbor of v
				if (level[w] == -1) {   // w has not already been reached
					parent[w] = v;
					level[w] = thislevel+1;
					levelsize[thislevel+1]++;
					queue[back++] = w;    // put w on queue to explore
				}
			}
		}
		thislevel = thislevel+1;
	}
	*nlevelsp = thislevel;
	free(queue);
}

#define getRandom() (drand48())

void randPerm(int n, unsigned int perm[])
{
  int i, j, t;

  for(i=0; i<n; i++)
    perm[i] = i;

  for(i=0; i<n; i++) {
    j = rand()%(n-i)+i;
    t = perm[j];
    perm[j] = perm[i];
    perm[i] = t;
  }
}

int generateEdges(int SCALE, int edgefactor, unsigned int **head, unsigned int **tail){
   
  unsigned int N =  (((unsigned int)1) << SCALE); // Set the number of vertices
  
  unsigned int M = (edgefactor * N); // Set the number of edges

  double const A = 0.57;
  double const B = 0.19;
  double const C = 0.19;
  


  double const ab = (A+B); 
  double const c_norm = C / (1 - ab);
  double const a_norm = A / ab;

  unsigned int ib;
  unsigned int randNum;

  // Set the seeds for the drand48 and the rand function
  //  srand48((long int)time(NULL));
  //srand((long int)time(NULL));
  srand(928);
  int ii_bit, jj_bit;

	*head = (unsigned int *) malloc (M*sizeof(unsigned int));
	*tail = (unsigned int *) malloc (M*sizeof(unsigned int));
  unsigned int j;
  for(ib = 1; ib <= SCALE; ib++) {
    
    for(j = 0; j < M; j++) {
      ii_bit = (getRandom() > ab);
      jj_bit = (getRandom() > (c_norm * ii_bit + a_norm * !(ii_bit)));
      (*tail)[j] += ((unsigned int)1 << (ib - 1)) * ii_bit;
      (*head)[j] += ((unsigned int)1 << (ib - 1)) * jj_bit;
    }
  }
  
  unsigned int * p = (unsigned int *) malloc(N*sizeof(unsigned int)); 
  if(p == NULL) {
    printf("Malloc failed for permutation array p\n");
    exit(-1);
  }
  
  // Permute the vertices
  randPerm(N,p);

  for(j = 0; j < M; j++) {
    unsigned int index = (*tail)[j];
    (*tail)[j] = p[index];
    index = (*head)[j];
    (*head)[j] = p[index];
  }

  free(p);
  

  
  return M;
}