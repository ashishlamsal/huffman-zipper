#pragma once
#include<iostream>

class Decompressor {

	std::unordered_map<char, std::string> codeMap;
	std::ifstream infile;
	void readHeader();
	std::string readAllCharFromFile();
	std::string extractTextFromFile();
	
public:
	void decompressor(std::string infileName);

};