//
//  pbfs.cpp
//  finalx
//
//  Created by Tyler Weimin Ouyang on 3/6/15.
//  Copyright (c) 2015 Tyler Weimin Ouyang & Jenna Cryan. All rights reserved.
//

#include "Header.h"
#include <list>
using namespace std;

void pbfsList(graph *G, Vertex *root, int **levelp, int *nlevelsp, int **levelsizep, int **parentp){
	
	int *level, *levelsize;
	level = *levelp = (int *) calloc(G->nv+1, sizeof(int));
	levelsize = *levelsizep = (int *) calloc(G->nv+1, sizeof(int));
	int currentLevel = 1;
	
	list<Vertex*> frontier;
	frontier.push_front(root);
	int* parent = new int[G -> nv + 1];
	*parentp = parent;
	while( !frontier.empty() )
	{
		Vertex **vtxArr = new Vertex*[frontier.size()];
		Vertex **arrPtr = vtxArr;
		for (auto it = frontier.begin(); it != frontier.cend(); ++it){
			*arrPtr++ = *it;
		}
		cilk_for( int i = 0; i < frontier.size(); ++i ) {
			for ( int v = 0; v < vtxArr[i]->getNumOfAdjacency(); v++ ) {
				if( !vtxArr[i]->getAdjacency()[v]->isVisited()) {
					parent[vtxArr[i]->getAdjacency()[v]->getVertexNum()] = vtxArr[i]->getVertexNum(); // ?
				}
			}
		}
		cilk::hyperobject< reducer_list_append<Vertex*> > nextlist();
		cilk_for (int i = 0; i < frontier.size(); i++ ) {
			//for( Vertex v in frontier[i].adjacency() )
			for (int v = 0; v < vtxArr[i]->getNumOfAdjacency(); v++) {
				if (parent[vtxArr[i]->getAdjacency()[v]->getVertexNum()] == vtxArr[i]->getVertexNum()) {
					nextlist.push_back(vtxArr[i] -> getAdjacency()[v]);
					vtxArr[i] -> getAdjacency()[v]->setVisited();
					
					levelsize[currentLevel]++;
					level[vtxArr[i]->getAdjacency()[v]->getVertexNum()] = currentLevel;
				}
			}
		}
		frontier = nextlist.get_value();
		delete[] vtxArr;
		
		currentLevel++;
	}
	*nlevelsp = currentLevel-1;
}


