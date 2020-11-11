#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <bitset>

#include "BinNode.h"
#include "PriorityQueue.h"
#include "HashMap.h"

#define INTERNAL_NODE_CHARACTER '$'

HashMap<char, std::string> codeMap;
void encodeCharacters(BinNode* rootNode, std::string codeString) {
	if (rootNode == nullptr)
		return;
	if (rootNode->getCharacter() != '$') {
		codeMap[rootNode->getCharacter()] = codeString;
	}

	encodeCharacters(rootNode->getLeftChild(), codeString + "0");
	encodeCharacters(rootNode->getRightChild(), codeString + "1");
}

std::string decodeCharacters(BinNode* root, std::string encodedString) {
	std::string decodedString = "";
	BinNode* curr = root;
	for (int i = 0; i < encodedString.size(); i++) {
		if (encodedString[i] == '0')
			curr = curr->getLeftChild();
		else
			curr = curr->getRightChild();

		// reached leaf node 
		if (curr->getLeftChild() == nullptr && curr->getRightChild() == nullptr) {
			decodedString += curr->getCharacter();
			curr = root;
		}
	}
	return decodedString;
}
BinNode* buildDecodingTree(HashMap<char, std::string>& encodingMap) {

	BinNode* rootNode = new BinNode(INTERNAL_NODE_CHARACTER, int());
	BinNode* previousNode;

	for (auto&& item : encodingMap) {
		previousNode = rootNode;
		std::string& characterCode = item.value;
		for (int i = 0; i < characterCode.size(); i++) {
			if (characterCode[i] == '0') {
				if (i == characterCode.size() - 1)		// last character
					previousNode->setLeftChild(new BinNode(item.key, int()));
				else {
					if (!previousNode->getLeftChild())
						previousNode->setLeftChild(new BinNode(INTERNAL_NODE_CHARACTER, int()));
					previousNode = previousNode->getLeftChild();
				}
			}
			else {
				if (i == characterCode.size() - 1)
					previousNode->setRightChild(new BinNode(item.key, int()));
				else {
					if (!previousNode->getRightChild())
						previousNode->setRightChild(new BinNode(INTERNAL_NODE_CHARACTER, int()));
					previousNode = previousNode->getRightChild();
				}
			}
		}
	}
	return rootNode;
}


int main() {
	// read file
	std::ifstream infile("./src/small-text.txt");
	if (!infile) {
		std::cout << "Error: File couldn't be opened." << std::endl;
		exit(1);
	}

	std::cout << "Success: File opened successfully." << std::endl;

	//get frequency
	char ch;
	HashMap<char, int> frequency;
	while (!infile.eof()) {
		infile.get(ch);
		frequency[ch]++;
	}
	infile.close();

	for (auto&& character : frequency)
		std::cout << character.key << "=" << character.value << std::endl;
	
	//priority queue 
	PriorityQueue<BinNode*> pq;
	for (auto&& character : frequency) {
		pq.enqueue(new BinNode(character.key, character.value));
	}

	pq.display();

	std::cout << "Building Tree1...\n";
	while (pq.getSize() != 1)
	{
		BinNode* left = pq.dequeue();
		BinNode* right = pq.dequeue();
		BinNode* new_pair = new BinNode('$', left->getFrequency() + right->getFrequency());
		pq.enqueue(new_pair);
		new_pair->setLeftChild(left);
		new_pair->setRightChild(right);
	}

	//generate Huffman codes
	encodeCharacters(pq.top(), "");

	for (auto&& code : codeMap)
		std::cout << code.key << "=" << code.value << ", ";


	//encoded string
	char character;
	std::string encodedString;
	std::ifstream inputStream("./src/small-text.txt");
	while (inputStream.get(character))
		encodedString += codeMap[character];
	inputStream.close();
	std::cout << encodedString << std::endl;

	////decoded string
	BinNode* root = buildDecodingTree(codeMap);
	std::cout << decodeCharacters(root, encodedString);


	//TODO
	// 1. Write encodedString to file
	// 2. Read encodedString from file
	// 3. Build decoding tree
	// 4. decode string
	// 5. write decoded string to file

	return 0;
}