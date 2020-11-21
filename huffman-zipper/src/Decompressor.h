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

class Decompressor {
private:
	HashMap<char, std::string> codeMap;
	
	std::ifstream infile;
	std::fstream tempFile;
	std::ofstream outfile;
	BinNode* rootNode;

private:
	void readHeader();
	void readAllCharFromFile();

	void buildDecodingTree();
	void decodeCharacters(const std::string& outfileName);
	void deleteTree(BinNode* node);

public:
	Decompressor();
	~Decompressor();
	void decompressFile(const std::string& infileName);
};