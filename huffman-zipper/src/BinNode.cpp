#include "BinNode.h"

BinNode::BinNode(char character, int frequency) {

	this->character = character;
	this->frequency = frequency;
	this->leftChild = this->rightChild = nullptr;
}

char BinNode::getCharacter() const {
	return character;
}

int BinNode::getFrequency() const {
	return frequency;
}

void BinNode::setLeftChild(BinNode* left) {
	BinNode::leftChild = left;
}

void BinNode::setRightChild(BinNode* right) {
	BinNode::rightChild = right;
}

BinNode* BinNode::getLeftChild() const {
	return leftChild;
}

BinNode* BinNode::getRightChild() const {
	return rightChild;
}