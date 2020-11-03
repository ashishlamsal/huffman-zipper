#pragma once
#include "MinHeap.h"

template <class T>
class PriorityQueue
{
private:
	MinHeap<T> heap;
public:
	void enqueue(const T&);
	T dequeue();
	bool isEmpty();
	void display();
};

