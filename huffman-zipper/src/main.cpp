#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <string>
#include <sstream>
#include <bitset>

#include "BinNode.h"
//#include "PriorityQueue.h"
#include "MinHeap.h"

class Comparator {
public:
	bool operator()(BinNode* first, BinNode* second) {
		return first->getFrequency() > second->getFrequency();
	}
};

std::unordered_map<char, std::string> codeMap;
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


int main() {
	MinHeap<int> heap;
	heap.insert(5);
	heap.insert(10);
	heap.insert(17);
	heap.insert(4);
	heap.insert(22);
	heap.insert(30);
	heap.insert(15);
	heap.display();
	std::cout << heap.remove() << " is removed" << std::endl;
	std::cout << heap.remove() << " is removed" << std::endl;
	heap.display();
	std::cout << heap.remove() << " is removed" << std::endl;
	heap.display();

	//PriorityQueue<float> pqueue;
	//pqueue.enqueue(30.5);
	//pqueue.enqueue(20.2);
	//pqueue.enqueue(40.6);
	//pqueue.enqueue(10.6);
	//pqueue.display();
	//std::cout << pqueue.dequeue() << " is removed" << std::endl;
	//pqueue.display();



	// read file
	std::ifstream infile("./src/small-text.txt");
	if (!infile) {
		std::cout << "Error: File couldn't be opened." << std::endl;
		exit(1);
	}

	std::cout << "Success: File opened successfully." << std::endl;

	//get frequency
	char ch;
	std::unordered_map<char, int> frequency;
	while (!infile.eof()) {
		infile.get(ch);
		frequency[ch]++;
	}
	infile.close();

	for (auto&& character : frequency)
		std::cout << character.first << "=" << character.second << std::endl;

	// priority queue
	std::priority_queue<BinNode*, std::vector<BinNode*>, Comparator> pq;
	for (auto&& character : frequency) {
		pq.push(new BinNode(character.first, character.second));
	}

	std::cout << "Building Tree...\n";
	while (pq.size() != 1)
	{
		BinNode* left = pq.top();
		pq.pop();
		BinNode* right = pq.top();
		pq.pop();
		BinNode* new_pair = new BinNode('$', left->getFrequency() + right->getFrequency());
		pq.push(new_pair);
		new_pair->setLeftChild(left);
		new_pair->setRightChild(right);
	}

	// generate Huffman codes
	encodeCharacters(pq.top(), "");

	for (auto&& code : codeMap)
		std::cout << code.first << "=" << code.second << std::endl;


	//encoded string
	char character;
	std::string encodedString;
	std::ifstream inputStream("./src/small-text.txt");
	while (inputStream.get(character))
		encodedString += codeMap[character];
	inputStream.close();
	std::cout << encodedString << std::endl;

	//decoded string
	std::cout << decodeCharacters(pq.top(), encodedString);

	//TODO
	// 1. Write encodedString to file
	// 2. Read encodedString from file
	// 3. Build decoding tree
	// 4. decode string
	// 5. write decoded string to file

	//write to file
	//char character;
	//std::string file;
	//std::ifstream inputStream("./src/small-text.txt");
	//std::ofstream outputStream("./src/out.txt");
	////writeHeader(outputStream);

	//while (inputStream.get(character))
	//	file += codeMap[character];
	//inputStream.close();

	//file += codeMap[PSEUDO_EOF];
	//	unsigned long remainder = (file.size() - 1) % 8;
	//	for (int i = 0; i < 8 - remainder; ++i)
	//		file += '0';
	//	std::stringstream stringStream(file);
	//
	//	while (stringStream.good()) {
	//		std::bitset<8> bits;
	//		stringStream >> bits;
	//		char c = char(bits.to_ulong());
	//		outputStream << c;
	//	}	
	//	outputStream.flush();
	//	outputStream.close();

	return 0;
};