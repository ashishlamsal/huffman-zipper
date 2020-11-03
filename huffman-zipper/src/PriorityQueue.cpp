#include "PriorityQueue.h"

template class PriorityQueue<float>;

template <class T>
bool PriorityQueue<T>::isEmpty() {
	return heap.isEmpty();
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
void PriorityQueue<T>::display() {
	std::cout << "Priority Queue ";
	heap.display();
}