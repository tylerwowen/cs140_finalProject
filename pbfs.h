//
//  pbfs.h
//  finalx
//
//  Created by Tyler Weimin Ouyang on 3/6/15.
//  Copyright (c) 2015 Tyler Weimin Ouyang & Jenna Cryan. All rights reserved.
//

#ifndef __finalx__pbfs__
#define __finalx__pbfs__

#include "Header.h"

void pbfs(graph *g, Node *v0);
void process_layer(Bag* in_bag, Bag* out_bag, int d);


#endif /* defined(__finalx__pbfs__) */
