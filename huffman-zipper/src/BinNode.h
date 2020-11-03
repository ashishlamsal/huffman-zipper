#pragma once

class BinNode {
private:
	char character;
	int frequency;
	BinNode* leftChild;
	BinNode* rightChild;

public:
	BinNode(char, int);

	char getCharacter() const;
	int getFrequency() const;

	BinNode* getLeftChild() const;
	BinNode* getRightChild() const;

	void setLeftChild(BinNode*);
	void setRightChild(BinNode*);
};
