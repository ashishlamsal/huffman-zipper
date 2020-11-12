#pragma once
#include <iostream>

class BinNode {
private:
	char character;
	int frequency;
	BinNode* leftChild;
	BinNode* rightChild;

public:
	BinNode(char, int);

	friend std::ostream& operator<<(std::ostream&, BinNode*);
	friend std::ostream& operator<<(std::ostream&, const BinNode&);
	bool operator<(const BinNode&);
	bool operator<=(const BinNode&);


	char getCharacter() const;
	int getFrequency() const;

	BinNode* getLeftChild() const;
	BinNode* getRightChild() const;

	void setLeftChild(BinNode*);
	void setRightChild(BinNode*);
};
