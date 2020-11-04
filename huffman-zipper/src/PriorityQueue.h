#pragma once
#include "MinHeap.h"

template <class T>
class PriorityQueue
{
private:
	MinHeap<T> heap;
public:
	PriorityQueue() {}

	void enqueue(const T&);
	T dequeue();
	T top();

	bool isEmpty();
	int getSize();

	void display();
};

