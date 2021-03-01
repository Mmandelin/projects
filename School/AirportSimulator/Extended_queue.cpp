#include "Extended_queue.h"

bool Extended_queue::full() const
{
	//return false;
	return count == maxqueue;	//return true if que is full
}

int Extended_queue::size() const
/*
Post:   Return the number of entries in the Extended_queue.
*/
{
	return count;
}

void Extended_queue::clear()
{
	this->count = 0;
	this->front = 0;
	this->rear = maxqueue - 1;
}

Error_code Extended_queue::serve_and_retrieve(Queue_entry& item)
{
	if (count <= 0) return underflow;
	item = entry[front];
	count--;
	front = ((front + 1) == maxqueue) ? 0 : (front + 1);
	return success;
}

