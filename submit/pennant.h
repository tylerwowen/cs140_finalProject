//
//  pennant.h
//  finalx
//
//  Created by Tyler Weimin Ouyang on 3/8/15.
//  Copyright (c) 2015 Tyler Weimin Ouyang & Jenna Cryan. All rights reserved.
//

#ifndef __finalx__pennant__
#define __finalx__pennant__

#include <stdio.h>
#include "Header.h"

class Pennant {
private:
	Node* root_;
	unsigned long size_;
public:
	Pennant();
	Pennant(Node* node);
	~Pennant();
	void merge(Pennant* pen2); // Pennant-Union
	Pennant* merge2(Pennant* pen2);
	Pennant* split();
	unsigned long getSize();
};


#endif /* defined(__finalx__pennant__) */
