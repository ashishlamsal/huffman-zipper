#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <chrono>

#include "HashMap.h"
#include "BinNode.h"

class Decompressor {
private:
	HashMap<char, std::string> codeMap;
	std::ifstream infile;
	std::fstream tempFile;

private:
	void readHeader();
	void readAllCharFromFile();
	BinNode* buildDecodingTree();
	void decodeCharacters(BinNode* root);

public:
	~Decompressor();
	void decompressor(std::string infileName);
};