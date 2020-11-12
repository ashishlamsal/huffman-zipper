#pragma once
#include<iostream>
#include<fstream>
#include<bitset>
#include<string>
#include "HashMap.h"
#include "BinNode.h"



class Decompressor {

	HashMap<char, std::string> codeMap;
	std::ifstream infile;
	void readHeader();
	std::string readAllCharFromFile();
	std::string extractTextFromFile();
	BinNode* buildDecodingTree();
	std::string decodeCharacters(BinNode* root, std::string encodedString);
	void writeIntoFile(const std::string &decodedString);
	
public:
	void decompressor(std::string infileName);

};