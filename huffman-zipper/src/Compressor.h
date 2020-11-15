#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <bitset>
#include <chrono>

#include "BinNode.h"
#include "HashMap.h"
#include "PriorityQueue.h"
#include "Constants.h"

class Compressor {
private:
	std::ifstream infile;
	HashMap<char, int> frequency;
	HashMap<char, std::string> codeMap;

private:
	HashMap<char, int> getFrequency();
	
	BinNode* createHuffmanTree();
	void generateHuffmanCode(BinNode* rootNode, std::string codeString);
	std::string generateEncodedString();
	
	void writeHeader(std::ofstream& outfile);
	void encodeIntoFile(std::string encodedString, std::string outfileName);
	void deleteTree(BinNode* node);

public:
	void compressor(std::string infileName);
};
