#include "BinNode.h"

BinNode::BinNode(char character, int frequency) {
	this->character = character;
	this->frequency = frequency;
	this->leftChild = this->rightChild = nullptr;
}

std::ostream& operator<<(std::ostream& os, BinNode* node) {
	os << node->getCharacter() << "=" << node->getFrequency() << std::flush;
	return os;
}

std::ostream& operator<<(std::ostream& os, const BinNode& node) {
	os << node.getCharacter() << "=" << node.getFrequency() << std::flush;
	return os;
}

bool BinNode::operator<(const BinNode& other) {
	return this->getFrequency() < other.getFrequency();
}

bool BinNode::operator<=(const BinNode& other) {
	return this->getFrequency() <= other.getFrequency();
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