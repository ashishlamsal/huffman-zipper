#pragma once
#include <vector>
#include <stdexcept>

#include "Constants.h"

/**
 * This class models a linear structure called a Queue.

 * In queue ,values are added at one end and removed from the other.
 * This discipline gives rise to a first-in/first-out behavior (FIFO). 
 */
template <typename ValueType>
class Queue {
private:
	std::vector<ValueType> ringBuffer;	/**< Vector of ValueType for Circular Queue */
	int front;							/**< index to front of the queue */
	int rear;							/**< index to rear of the queue */

	int count;							/**< number of value in the queue */
	int capacity;						/**< capacity of the queue */

private:

	/**
	 * This private method doubles the capacity of the ringBuffer vector.  
	 * It also shifts all the elements back to the beginning of the vector.
	 */
	void expandRingBufferCapacity();

public:
	/** Initializes a new empty queue. */
	Queue();

	/** Frees any heap storage associated with this queue. */
	virtual ~Queue() = default;

	/** Removes all elements from the queue. */
	void clear();

	/** @returns the number of values in the queue. */
	int size() const;

	/** @returns true if the queue contains no elements. */
	bool isEmpty() const;
	
	/** Adds value to the end of the queue. */
	void enqueue(const ValueType& value);

	/** Removes and returns the first item in the queue. */
	ValueType dequeue();

	/** @returns the first value in the queue, without removing it */
	ValueType peek() const;

	/** @returns the first value in the queue by reference. */
	ValueType& getFront();
	
	/** @returns the last value in the queue by reference. */
	ValueType& getBack();
};

/************************************************************************/
/* implementation                                                       */
/************************************************************************/

template <typename ValueType>
Queue<ValueType>::Queue() :front(0), rear(0), count(0), capacity(INITIAL_QUEUE_CAPACITY) {
	ringBuffer = std::vector<ValueType>(capacity);
}

template <typename ValueType>
int Queue<ValueType>::size() const {
	return count;
}

template <typename ValueType>
bool Queue<ValueType>::isEmpty() const {
	return count == 0;
}

template <typename ValueType>
void Queue<ValueType>::clear() {
	capacity = INITIAL_QUEUE_CAPACITY;
	ringBuffer = std::vector<ValueType>(capacity);
	front = 0;
	rear = 0;
	count = 0;
}

template <typename ValueType>
void Queue<ValueType>::enqueue(const ValueType& value) {
	if (count >= capacity - 1)
		expandRingBufferCapacity();

	ringBuffer[rear] = value;
	rear = (rear + 1) % capacity;
	count++;
}

template <typename ValueType>
ValueType Queue<ValueType>::dequeue() {
	if (isEmpty())
		throw std::runtime_error("dequeue: Attempting to dequeue an empty queue");

	ValueType result = ringBuffer[front];
	front = (front + 1) % capacity;
	count--;
	return result;
}

template <typename ValueType>
ValueType Queue<ValueType>::peek() const {
	if (isEmpty())
		throw std::runtime_error("peek: Attempting to peek at an empty queue");
	return ringBuffer.get(front);
}

template <typename ValueType>
ValueType& Queue<ValueType>::getFront() {
	if (isEmpty())
		throw std::runtime_error("front: Attempting to read front of an empty queue");
	return ringBuffer[front];
}

template <typename ValueType>
ValueType& Queue<ValueType>::getBack() {
	if (isEmpty())
		throw std::runtime_error("back: Attempting to read back of an empty queue");
	return ringBuffer[(rear + capacity - 1) % capacity];
}

template <typename ValueType>
void Queue<ValueType>::expandRingBufferCapacity() {
	std::vector<ValueType> copyBuffer = ringBuffer;
	ringBuffer = std::vector<ValueType>(2 * capacity);
	for (int i = 0; i < count; i++) {
		ringBuffer[i] = copyBuffer[(front + i) % capacity];
	}
	front = 0;
	rear = count;
	capacity *= 2;
}