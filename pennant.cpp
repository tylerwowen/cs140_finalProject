//
//  pennant.cpp
//  finalx
//
//  Created by Tyler Weimin Ouyang on 3/8/15.
//  Copyright (c) 2015 Tyler Weimin Ouyang & Jenna Cryan. All rights reserved.
//

#include "pennant.h"

Pennant::Pennant() {
	root_ = NULL;
	size_ = 0;
}

Pennant::Pennant(Node* node) {
	root_ = node;
	root_->left_ = NULL;
	root_->right_ = NULL;
	size_ = 1;
}

Pennant::~Pennant(){
	delete [] root_;
}

// Merge pen2 into this
void Pennant::merge(Pennant* pen2){
	pen2->root_->right_ = root_->left_;
	root_->left_ = pen2->root_;
	size_+=pen2->size_;
}

// Merge pen2 into this and return this
Pennant* Pennant::merge2(Pennant* pen2){
	pen2->root_->right_ = root_->left_;
	root_->left_ = pen2->root_;
	size_+=pen2->size_;
	return this;
}

Pennant* Pennant::split() {
	Pennant* newBag = new Pennant();
	newBag->root_ = root_->left_;
	root_->left_ = newBag->root_->right_;
	newBag->root_->right_ = NULL;
	newBag->size_ = size_/2;
	size_ = size_/2;
	return newBag;
}

unsigned long Pennant::getSize(){
	return size_;
}