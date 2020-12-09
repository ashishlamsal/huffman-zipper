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

/**
 * This class decompresses compressed(.huf) files to its original form.
 *
 * It decompresses those files and folders which was compressed using 
 * Huffman Compression Algorithm.
 */
class Decompressor {
private:

	/** 
	* Structure to hold file metadata. 
	* 
	* Used to retain original file(s) with its filename and relative path.
	* e.g. if fileSize = 143 and filePath = "/abc/input.txt" 
	* Creates 'input.txt' inside 'abc' directory of 143 bytes after decompression. 
	*/
	struct fileInfo {
		int fileSize;		/**< number of character in file. */
		fs::path filePath;	/**< path of file including filename and extension. */

		fileInfo() :fileSize(0) {}
		fileInfo(const int& fileSize, const fs::path& filePath) :fileSize(fileSize), filePath(filePath) {}
	};

	/** Queue of input file(s) to be decompressed. */
	Queue<fileInfo> files;
	
	/** Instance of ifstream class for reading encoded characters from compressed file.*/
	std::ifstream infile;

	/** Root node for Huffman tree.										*/
	BinNode* rootNode;

private:

	/** Resets all the attributes for next decompression operation. */
	void clear();
	
	/** Frees all heap storage associated with the Huffman Tree.	 */
	void deleteTree(BinNode* node);
	
	/**
	 *  Reads the header section from compressed file.
	 *
	 * Header section of compressed file contains tree and other metaData
	 * required during decompression.
	 * Meta data includes number of input files, each file size and file path
	 */
	void readHeader(const std::string& infileName, std::ifstream& infile);
	
	/**
	 *  Reads the entire Huffman tree in to the file header section
	 *  using a pre-order traversal algorithm.
	 * 
	 * when the program reads a bit 1, it can read the next 8 bits and wrap the 
	 * char in a binary leaf node. When the program reads a bit 0, it create a 
	 * new internal node and connect the two nodes as left and right child.
	 */
	BinNode* readTree(std::ifstream& reader);
	
	/**
	 * Decodes encoded characters using the tree obtained from header section.
	 * 
	 * Traverses the tree and on reaching the leaf node, write the character
	 * present in leaf node to output file till all the characters are decoded.
	 * 
	 * If output file size becomes equal to the fileSize known from file header
	 * section, it flush and closes the file and creates a new output file from 
	 * the files queue till it becomes empty. 
	 */
	void writeIntoFile(const std::string& infileName);

public:
	Decompressor();
	~Decompressor();
	
	/**
	 *  Decompresses the compressed(.huf) file to its original form.
	 *
	 * @param infileName compressed file path to be decompressed.
	 */
	void decompressFile(const std::string& infileName);
};