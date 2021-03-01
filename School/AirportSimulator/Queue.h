#pragma once
#include "Utility.h"
#include "Plane.h"

typedef Plane Queue_entry;
const int maxqueue = 100; //  queue size

class Queue {
public:
	Queue();
	bool empty() const;
	Error_code serve();
	Error_code append(const Queue_entry& item);
	Error_code retrieve(Queue_entry& item) const;
	int getCount() const;

protected:
	int count;
	int front, rear;
	Queue_entry entry[maxqueue];
};