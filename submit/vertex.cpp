//
//  vertex.cpp
//  finalx
//
//  Created by Tyler Weimin Ouyang on 3/15/15.
//  Copyright (c) 2015 Golden. All rights reserved.
//

#include "vertex.h"

Vertex::Vertex(){
	adjacency = NULL;
	visited = false;
}

Vertex::Vertex(unsigned int vertexNum, unsigned int num){
	this->vertexNum = vertexNum;
	numOfAdjacency = num;
	visited = false;
	adjacency = new Vertex*[num];
}

Vertex::~Vertex(){
	delete [] adjacency;
}

bool Vertex::isVisited(){
	return visited;
}

void Vertex::setVisited(){
	visited = true;
}

void Vertex::addNeighbor(Vertex *neighbor, int loc){
	adjacency[loc] = neighbor;
}

unsigned int Vertex::getNumOfAdjacency(){
	return numOfAdjacency;
}

unsigned int Vertex::getVertexNum(){
	return vertexNum;
}

Vertex* Vertex::getNthAdjacency(int index){
	return adjacency[index];
}