//
//  bag.h
//  finalx
//
//  Created by Tyler Weimin Ouyang on 3/6/15.
//  Copyright (c) 2015 Tyler Weimin Ouyang & Jenna Cryan. All rights reserved.
//

#ifndef finalx_bag_h
#define finalx_bag_h

#include "bag.h"
#include "pennant.h"

class Bag {
private:
	Pennant **backbone;
	unsigned long numNodes;
public:
	Bag();
	Bag(int n);
	~Bag();
	void insert(Pennant* pen);
	void merge(Bag* bag2);
	Bag* split();
	unsigned long getNumNodes();
};

void FA(Pennant *x, Pennant *y, Pennant *z);

#endif
