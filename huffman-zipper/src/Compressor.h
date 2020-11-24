#pragma once
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <string>
#include <chrono>
#include <filesystem>

#include "BinNode.h"
#include "HashMap.h"
#include "PriorityQueue.h"
#include "Constants.h"

namespace fs = std::filesystem;

class Compressor {
private:
	HashMap<char, int> frequency;
	HashMap<char, std::string> codeMap;

	BinNode* rootNode;
	std::string metaData;
	uint16_t fileCount;

	std::ifstream infile;

private:
	BinNode* createHuffmanTree();
	void generateHuffmanCode(BinNode* rootNode, std::string codeString);
	void deleteTree(BinNode* node);

	void readFrequency();
	void scanPath(const std::string& pathName);
	void scanFile(const std::string& infileName);

	void writeTree(std::ofstream& writer, BinNode* head);
	void writeHeader(std::ofstream& writer);
	void writeBody(char& chr, int& bufferSize, const std::string& infileName, std::ofstream& writer);
	void writeIntoFile(const std::string& infileName, const std::string& outfileName);

	void compress(const std::string& infileName);

public:
	Compressor();
	~Compressor();

	void compressFile(const std::string& infileName);
	void compressFolder(const std::string& directoryName);

};