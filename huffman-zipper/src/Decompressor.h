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
	struct fileInfo {
		int fileSize;
		fs::path filePath;

		fileInfo() :fileSize(0) {}
		fileInfo(const int& fileSize, const fs::path& filePath) :fileSize(fileSize), filePath(filePath) {}
	};

	Queue<fileInfo> files;
	std::ifstream infile;

	BinNode* rootNode;

private:
	void clear();
	void deleteTree(BinNode* node);
	
	void readHeader(const std::string& infileName, std::ifstream& infile);
	BinNode* readTree(std::ifstream& reader);
	void writeIntoFile(const std::string& infileName);

public:
	Decompressor();
	~Decompressor();
	
	void decompressFile(const std::string& infileName);
};