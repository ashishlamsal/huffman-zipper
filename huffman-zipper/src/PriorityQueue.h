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

// implementation
template <class T>
bool PriorityQueue<T>::isEmpty() {
	return heap.isEmpty();
}

template <class T>
int PriorityQueue<T>::getSize() {
	return heap.getSize();
}

template <class T>
void PriorityQueue<T>::enqueue(const T& value) {
	heap.insert(value);
}

template <class T>
T PriorityQueue<T>::dequeue() {
	return heap.remove();
}

template <class T>
T PriorityQueue<T>::top() {
	return heap.min();
}

template <class T>
void PriorityQueue<T>::display() {
	std::cout << "Priority Queue : ";
	heap.display();
}