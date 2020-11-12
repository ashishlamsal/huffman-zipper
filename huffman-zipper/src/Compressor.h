#pragma once
#include<iostream>
#include"HashMap.h"
#include<fstream>
#include<sstream>
#include<bitset>

#include"BinNode.h"
#include "PriorityQueue.h"
#include "Constants.h"



class Compressor {
private:
	std::ifstream infile;
	HashMap<char, int> frequency;
	HashMap<char, std::string> codeMap;
	HashMap<char, int> getFrequency();
	BinNode* createHuffmanTree();
	void generateHuffmanCode(BinNode* rootNode, std::string codeString);
	void writeHeader(std::ofstream& outfile);
	void encodeIntoFile(std::string encodedString, std::string outfileName);
	std::string generateEncodedString();
public:
	
	void compressor(std::string infileName);

};
