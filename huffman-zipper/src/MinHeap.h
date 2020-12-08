#pragma once
#include <iostream>
#include <vector>
#include <type_traits>

#include "BinNode.h"
#include "Constants.h"


/**
 * This class models a structure called a MinHeap in which value
 * in the root node is minimum.
 * 
 * It is a complete binary tree in which the value contained in each node 
 * is less than (or equal to) the value in that node's children.
 */
template <class T>
class MinHeap {
private:
	std::vector<T> items; /** Vector of items of MinHeap */

private:

	/** @returns parent index of a parameter index */
	int parent(int);

	/** @returns left child index of a parameter index */
	int leftChild(int);

	/** @returns right child index of a parameter index */
	int rightChild(int);

	/** @returns smaller child of parameter index */
	template< typename U = T >
	typename std::enable_if<std::is_pointer<U>::value, int >::type smallerChild(int index);
	template< typename U = T >
	typename std::enable_if<!std::is_pointer<U>::value, int >::type smallerChild(int index);

	/** @returns true if parameter index has left child */
	bool hasLeftChild(int);

	/** @returns true if parameter index has right child */
	bool hasRightChild(int);
	template< typename U = T >
	typename std::enable_if<std::is_pointer<U>::value, bool > ::type isValidParent(int index);
	template< typename U = T >
	typename std::enable_if<!std::is_pointer<U>::value, bool > ::type isValidParent(int index);

	/** Bubbles up the value to meet the MinHeap property. 
	 *  @see insert()
	 */
	template<typename U = T>
	typename std::enable_if<std::is_pointer<U>::value, void >::type bubbleUp();
	template<typename U = T>
	typename std::enable_if<!std::is_pointer<U>::value, void >::type bubbleUp();

	/** Bubbles down the value to meet the MinHeap property. 
	 * 	@see remove()
	 */
	void bubbleDown();

	/**
	 * swap two values in the items vector
	 * @param index of the two values to be swapped
	 */
	void swap(int, int);

public:
	MinHeap();
	~MinHeap();

	/** @returns true if the MinHeap contains no elements. */
	bool isEmpty();

	/** @returns the number of values in the MinHeap. */
	int getSize();

	/** @returns the minimum value in the MinHeap. */
	T min();

	/** Adds value of type T to the MinHeap. */
	void insert(const T&);

	/** Removes and returns the minimum value. 
	 * @returns root node
	 */
	T remove();	

	/** Prints the values of the MinHeap. */
	void display();
};

/************************************************************************/
/* implementation                                                       */
/************************************************************************/

template <class T>
MinHeap<T>::MinHeap() {
	items.reserve(RESERVE_SIZE);
}

template <class T>
MinHeap<T>::~MinHeap() {
	items.clear();
}

template <class T>
bool MinHeap<T>::isEmpty() {
	return getSize() == 0;
}

template <class T>
int MinHeap<T>::getSize() {
	return items.size();
}

template <class T>
int MinHeap<T>::parent(int index) {
	return (index - 1) / 2;
}

template <class T>
int MinHeap<T>::leftChild(int index) {
	return (index * 2) + 1;
}

template <class T>
int MinHeap<T>::rightChild(int index) {
	return (index * 2) + 2;
}

template <class T>
void MinHeap<T>::swap(int first, int second) {
	T temp = items[first];
	items[first] = items[second];
	items[second] = temp;
}

template <class T>
T MinHeap<T>::min() {
	if (isEmpty()) {
		std::cout << "ERROR: MinHeap Underflow" << std::endl;
		exit(1);
	}
	return items[0];
}

template <class T>
void MinHeap<T>::insert(const T& value) {
	items.push_back(value);
	bubbleUp();
}

template<typename T> template<typename U>
typename std::enable_if<std::is_pointer<U>::value, void >::type MinHeap<T>::bubbleUp() {
	int index = getSize() - 1;
	while (index > 0 && *items[index] < *items[parent(index)]) {
		swap(index, parent(index));
		index = parent(index);
	}
}

template<typename T> template<typename U>
typename std::enable_if<!std::is_pointer<U>::value, void >::type MinHeap<T>::bubbleUp() {
	int index = getSize() - 1;
	while (index > 0 && items[index] < items[parent(index)]) {
		swap(index, parent(index));
		index = parent(index);
	}
}

template <class T>
T MinHeap<T>::remove() {
	if (isEmpty()) {
		std::cout << "ERROR: MinHeap Underflow" << std::endl;
		exit(1);
	}

	T root = items[0];
	items[0] = items[getSize() - 1];
	bubbleDown();

	items.pop_back();
	return root;
}

template <class T>
void MinHeap<T>::bubbleDown() {
	int index = 0;
	while (index < getSize() && !isValidParent(index)) {
		int smallerIndex = smallerChild(index);
		swap(index, smallerIndex);
		index = smallerIndex;
	}
}

template <class T>
bool MinHeap<T>::hasLeftChild(int index) {
	return leftChild(index) < getSize();
}

template <class T>
bool MinHeap<T>::hasRightChild(int index) {
	return rightChild(index) < getSize();
}

template<typename T> template<typename U>
typename std::enable_if<std::is_pointer<U>::value, bool > ::type MinHeap<T>::isValidParent(int index) {
	if (!hasLeftChild(index))
		return true;
	if (!hasRightChild(index))
		return *items[index] <= *items[leftChild(index)];

	return *items[index] <= *items[leftChild(index)] && *items[index] <= *items[rightChild(index)];
}

template<typename T> template<typename U>
typename std::enable_if<!std::is_pointer<U>::value, bool  >::type MinHeap<T>::isValidParent(int index) {
	if (!hasLeftChild(index))
		return true;
	if (!hasRightChild(index))
		return items[index] <= items[leftChild(index)];

	return items[index] <= items[leftChild(index)] && items[index] <= items[rightChild(index)];
}

template<typename T> template<typename U>
typename std::enable_if<std::is_pointer<U>::value, int >::type MinHeap<T>::smallerChild(int index) {
	if (!hasLeftChild(index))
		return index;
	if (!hasRightChild(index))
		return leftChild(index);

	return (*items[leftChild(index)] < *items[rightChild(index)]) ?
		leftChild(index) : rightChild(index);
}

template<typename T> template<typename U>
typename std::enable_if<!std::is_pointer<U>::value, int >::type MinHeap<T>::smallerChild(int index) {
	if (!hasLeftChild(index))
		return index;
	if (!hasRightChild(index))
		return leftChild(index);

	return (items[leftChild(index)] < items[rightChild(index)]) ?
		leftChild(index) : rightChild(index);
}

template <class T>
void MinHeap<T>::display() {
	std::cout << "[  ";
	for (int i = 0; i < getSize(); i++)
	{
		std::cout << items[i] << ", ";
	}
	std::cout << "\b\b  ]\n";
}