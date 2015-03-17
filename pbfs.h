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
#include <cilk/cilk.h>
#include <cilk/reducer_list.h>
#include <cilk/reducer_opadd.h>

void pbfsList(graph *G, Vertex *root, int **levelp, int *nlevelsp, int **levelsizep, int **parentp);

#endif /* defined(__finalx__pbfs__) */

