#pragma once
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <string>
#include <bitset>
#include <chrono>
#include<filesystem>

#include "BinNode.h"
#include "HashMap.h"
#include "PriorityQueue.h"
#include "Constants.h"


class Compressor {
private:
	HashMap<char, int> frequency;
	HashMap<char, std::string> codeMap;
	
	BinNode* rootNode;
	std::string encodedString;
	
	std::ifstream infile;

private:
	void getFrequency();
	BinNode* createHuffmanTree();
	void generateHuffmanCode(BinNode* rootNode, std::string codeString);
	void generateEncodedString();
	
	void writeHeader(std::ofstream& outfile);
	void encodeIntoFile(const std::string& outfileName);
	void deleteTree(BinNode* node);

public:
	Compressor();
	~Compressor();

	void compressFile(const std::string& infileName);
	void compressFiles(const std::string& infileName);
	void compressFolder(const std::string& infileName);
};
