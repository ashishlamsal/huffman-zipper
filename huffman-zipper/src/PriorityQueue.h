#pragma once
#include "MinHeap.h"

/**
 * This class models Priority Queue in which values are processed in order of priority.
 * 
 * It uses MinHeap as underlying data structure. So, lower value have higher priorities. 
 */
template <class T>
class PriorityQueue {
private:

	/** MinHeap Data Structure for Priority Queue implementation. */
	MinHeap<T> heap;
public:

	/** Adds value to the priority queue  */
	void enqueue(const T&);

	/** Removes and returns the highest priority value. */
	T dequeue();

	/** @returns the highest priority value without removing it. */
	T top();

	/** @returns true if the priority queue contains no elements. */
	bool isEmpty();

	/** @returns the number of values in the priority queue. */
	int getSize();

	/** Prints the values of the priority queue. */
	void display();
};

/************************************************************************/
/* implementation                                                       */
/************************************************************************/

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