//
//  pennant.h
//  finalx
//
//  Created by Tyler Weimin Ouyang on 3/8/15.
//  Copyright (c) 2015 Tyler Weimin Ouyang & Jenna Cryan. All rights reserved.
//

#ifndef finalx_pennant_h
#define finalx_pennant_h

#include "Header.h"

class Pennant {
private:
	Node* root_;
	unsigned long size_;
public:
	Pennant();
	pennant(Node* node);
	~Pennant();
	void merge(Pennant* pen2); // Pennant-Union
	Pennant* split();
};

#endif
