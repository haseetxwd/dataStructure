#pragma once
#include "List.h"

template <typename T> class Queue :public List<T> {
	void enqueue(T const &e){ this->insertAsLast(e); }
	T& front(){ return this->header->succ->data; }
	T dequeue(){ return this->remove(this->header->succ); }
};