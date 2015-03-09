//
//  bag.cpp
//  finalx
//
//  Created by Tyler Weimin Ouyang on 3/6/15.
//  Copyright (c) 2015 Tyler Weimin Ouyang & Jenna Cryan. All rights reserved.
//

#include "bag.h"
#define BAGSIZE
Bag::Bag() {
	backbone = new Pennant*[BAGSIZE];
	numNodes = 0;
}

Bag::Bag() {
	delete[] backbone;
}

Bag::Bag(int n) {
	backbone = new pennant* [n];
	for(int i = 0; i < n; i++) {
		backbone[i] = NULL;
	}
}

void Bag::insert(Pennant* x) {
	int i = 0;
	while(i < BAGSIZE && backbone[i] != NULL;) {
		x->merge(backbone[i]);
		backbone[i++] = NULL;
	}
	backbone[i] = x;
	numNodes++;
}

// merge bag2 into this
void Bag::merge(Bag* bag2) {
	Pennant* y = new Pennant();
	for(int k = 0; k < BAGSIZE; k++) {
		FA(backbone[k], bag2->backbone[k], y);	
	}
	numNodes += bag2->numNodes;
}

Bag* Bag::split() {
	Bag* bag2 = new Bag();
	Pennant* y = backbone[0];
	backbone[0] = NULL;
	
	for(int i = 1; i < BAGSIZE; i++) {
		if(backbone[i] != NULL) {
			bag2->backbone[i-1] = backbone[i]->split();
			backbone[i-1] = backbone[i];
			backbone[i] = NULL;
			bag2->numNodes+= bag2->backbone[i-1]->size_;
			numNodes-= bag2->backbone[i-1]->size_;
		}
	}
	y != NULL ? insert(y) : y = NULL;
}

unsigned long Bag::getNumNodes() {
	return numNodes;
}

void FA(Pennant *x, Pennant *y, Pennant *z) {
	if(y == NULL && z == NULL) {
		return;
	}
	else if(x == NULL && z == NULL) {
		return;
	}
	else if(x == NULL && y == NULL) {
		return;
	}
	else if(z == NULL) {
		x = NULL;
		z = x->merge(y);
	}
	else if(y == NULL) {
		x = NULL;
		z = x->merge(z);
	}
	else if(x == NULL) {
		x = NULL;
		z = y->merge(z);
	}
	else {
		x = x;
		z = y->merge(z);
	}
}

