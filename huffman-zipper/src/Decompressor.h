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
	void readAllCharFromFile();
	BinNode* buildDecodingTree();
	void decodeCharacters(BinNode* root);

	
public:
	void decompressor(std::string infileName);

};