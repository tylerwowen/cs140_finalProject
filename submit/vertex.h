//
//  vertex.h
//  finalx
//
//  Created by Tyler Weimin Ouyang on 3/15/15.
//  Copyright (c) 2015 Golden. All rights reserved.
//

#ifndef __finalx__vertex__
#define __finalx__vertex__

#include <stdio.h>

class Vertex{
private:
	Vertex** adjacency;
	bool visited;
	unsigned int vertexNum;
	unsigned int numOfAdjacency;
public:
	Vertex();
	Vertex(unsigned int vertexNum, unsigned int numOfAdjacency);
	~Vertex();
	bool isVisited();
	Vertex* getNthAdjacency(int index);
	unsigned int getNumOfAdjacency();
	unsigned int getVertexNum();
	void setVisited();
	void addNeighbor(Vertex *neighbor, int loc);
};

#endif /* defined(__finalx__vertex__) */