#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <bitset>

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
	void writeHeader(std::ofstream& outfile);
	void encodeIntoFile(std::string encodedString, std::string outfileName);
	std::string generateEncodedString();

public:
	void compressor(std::string infileName);
};
