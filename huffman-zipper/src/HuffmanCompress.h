#pragma once
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <string>
#include <bitset>
#include <chrono>

#include "BinNode.h"
#include "HashMap.h"
#include "PriorityQueue.h"
#include "Constants.h"

class HuffmanCompress {
private:
	HashMap<char, int> frequency;
	HashMap<char, std::string> codeMap;

	int numChars;
	BinNode* rootNode;
	std::ifstream infile;

private:
	void readFrequency();
	BinNode* createHuffmanTree();
	void generateHuffmanCode(BinNode* rootNode, std::string codeString);

	void writeTree(std::ofstream& writer, BinNode* head);
	void writeIntoFile(const std::string& outfileName);
	void deleteTree(BinNode* node);

public:
	HuffmanCompress();
	~HuffmanCompress();

	void compressFile(const std::string& infileName);
};


