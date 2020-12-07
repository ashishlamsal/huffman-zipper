#pragma once
#include <iostream>

/**
 * This class models a node structure used for building Huffman Binary Tree.
 * 
 * It stores character and frequency data in a binary tree of character-frequency pair.
 */
class BinNode {
private:
	char character;			/**< Character present in input data.		*/
	int frequency;			/**< Number of occurrence of a character.	*/
	BinNode* leftChild;		/**< Pointer to the left child.				*/
	BinNode* rightChild;	/**< Pointer to the right child.			*/

public:
	BinNode(char);
	BinNode(char, int);

	/** This method overloads insertion operator for printing node object. */
	friend std::ostream& operator<<(std::ostream&, BinNode*);
	friend std::ostream& operator<<(std::ostream&, const BinNode&);
	
	/** This method overloads less than operator for comparing node. 
	 *  @returns true if frequency of caller node is less than that of parameter node.
	 */
	bool operator<(const BinNode&);
	
	/** This method overloads less than and equal to (<=) operator for 
	 *  comparing node.
	 *  @returns true if frequency of caller node is less than and equal
	 *  to that of parameter node.
	 */
	bool operator<=(const BinNode&);
		
	/** @returns character present in the caller node instance.					*/
	char getCharacter() const;

	/** @returns frequency of character present in the caller node instance.	*/
	int getFrequency() const;

	/** @returns pointer to the left child of the caller node instance.			*/
	BinNode* getLeftChild() const;

	/** @returns pointer to the right child of the caller node instance.		*/
	BinNode* getRightChild() const;

	/** sets parameter node as left child of the caller node instance.			*/
	void setLeftChild(BinNode*);
	
	/** sets parameter node as left child of the caller node instance.			*/
	void setRightChild(BinNode*);

	/** @returns <code>true</code> if the caller node instance is leaf node.	*/
	bool isLeaf();
};
