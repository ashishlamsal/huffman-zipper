#pragma once
#include <iostream>
#include <vector>

#include "BinNode.h"

template <class T>
class MinHeap {
private:
	std::vector<T> items;

private:
	// returns indexes of array (not item)
	int parent(int);
	int leftChild(int);
	int rightChild(int);
	int smallerChild(int);

	bool isValidParent(int);
	bool hasLeftChild(int);
	bool hasRightChild(int);

	void bubbleUp();
	void bubbleDown();
	void swap(int, int); // @param indexes

public:
	MinHeap();
	~MinHeap();

	bool isEmpty();
	int getSize();

	T min();
	void insert(const T&);
	T remove();      // removes root node (default)

	void display();
};
