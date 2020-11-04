#include "MinHeap.h"

template class MinHeap<int>;
template class MinHeap<float>;

template <class T>
MinHeap<T>::MinHeap() {
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

template <class T>
void MinHeap<T>::bubbleUp() {
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

template <class T>
bool MinHeap<T>::isValidParent(int index) {
	if (!hasLeftChild(index))
		return true;
	if (!hasRightChild(index))
		return items[index] <= items[leftChild(index)];

	return items[index] <= items[leftChild(index)] && items[index] <= items[rightChild(index)];
}

template <class T>
int MinHeap<T>::smallerChild(int index) {
	if (!hasLeftChild(index))
		return index;
	if (!hasRightChild(index))
		return leftChild(index);

	return (items[leftChild(index)] < items[rightChild(index)]) ?
		leftChild(index) : rightChild(index);
}

template <class T>
void MinHeap<T>::display() {
	std::cout << "Min Heap : [  ";
	for (int i = 0; i < getSize(); i++)
	{
		std::cout << items[i] << ", ";
	}
	std::cout << "\b\b  ]\n";
}
