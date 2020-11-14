#include "BinNode.h"

BinNode::BinNode(char character) :character(character), frequency(0), leftChild(nullptr), rightChild(nullptr) {}

BinNode::BinNode(char character, int frequency) : character(character), frequency(frequency), leftChild(nullptr), rightChild(nullptr) {}

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
	this->leftChild = left;
}

void BinNode::setRightChild(BinNode* right) {
	this->rightChild = right;
}

BinNode* BinNode::getLeftChild() const {
	return leftChild;
}

BinNode* BinNode::getRightChild() const {
	return rightChild;
}

bool BinNode::isLeaf() {
	return getLeftChild() == nullptr && getRightChild() == nullptr;
}
