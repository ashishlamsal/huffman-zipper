#pragma once
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <string>
#include <bitset>
#include <chrono>

#include "HashMap.h"
#include "BinNode.h"
#include "Constants.h"

class HuffmanDecompress {
private:
	std::ifstream infile;
	BinNode* rootNode;

private:
	BinNode* readTree(std::ifstream& reader);
	void writeIntoFile(const std::string& outfileName);

	void deleteTree(BinNode* node);

public:
	HuffmanDecompress();
	~HuffmanDecompress();
	void decompressFile(const std::string& infileName);
};