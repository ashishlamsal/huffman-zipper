#pragma once
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <string>
#include <chrono>
#include <filesystem>
#include <initializer_list>

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
	std::vector<fs::path> inputFiles;

	std::ifstream infile;

private:
	BinNode* createHuffmanTree();
	void generateHuffmanCode(BinNode* rootNode, std::string codeString);
	
	void clear();
	void deleteTree(BinNode* node);

	void readFrequency();
	void scanFile(const fs::path& infilePath);

	void writeTree(std::ofstream& writer, BinNode* head);
	void writeHeader(const std::string& inputName, std::ofstream& writer);
	void writeBody(char& chr, int& bufferSize, const std::string& infileName, std::ofstream& writer);
	void writeIntoFile(const std::string& infileName);

	void compress(const std::string& infileName);

public:
	Compressor();
	~Compressor();

	void compressFile(const std::string& infileName);
	void compressFolder(const std::string& directoryName);
	void compressFiles(std::initializer_list<std::string> infileNames);

};