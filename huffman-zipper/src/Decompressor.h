#pragma once
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <string>
#include <bitset>
#include <chrono>
#include <filesystem>

#include "Queue.h"
#include "HashMap.h"
#include "BinNode.h"
#include "Constants.h"

namespace fs = std::filesystem;

class Decompressor {
private:
	Queue<std::pair<int, fs::path>> files;
	
	std::ifstream infile;
	BinNode* rootNode;

private:
	void deleteTree(BinNode* node);
	
	void readHeader(const std::string& infileName, std::ifstream& infile);
	BinNode* readTree(std::ifstream& reader);
	void writeIntoFile(const std::string& infileName, const std::string& outfileName);

public:
	Decompressor();
	~Decompressor();
	
	void decompressFile(const std::string& infileName);
};