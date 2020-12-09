#pragma once
#include <iostream>
#include <iomanip>
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

/**
 * This class compresses files and folders using Huffman Compression Algorithm.
 *
 * It can compress single file or multiple files or an entire directory 
 * recursively into a compressed file (.huf file).
 */
class Compressor {
private:
	/** Frequency of occurrence for each unique symbol in the source.	*/
	HashMap<char, int> frequency; 
	
	/** Prefix-free binary code for each value of the source symbol.	*/
	HashMap<char, std::string> codeMap;

	/** Root node for Huffman tree.										*/
	BinNode* rootNode;

	/** List of input files given by the user.							*/
	std::vector<fs::path> inputFiles;

	/** Instance of ifstream class for reading characters from source.	*/
	std::ifstream infile;

private:
	/**
	 * Creates a Huffman Tree form unique characters along with their frequency of occurrences.
	 * 
	 * @returns root node of the Huffman Tree.
	 */
	BinNode* createHuffmanTree();

	/**
	 * Generates prefix code for each unique characters in the source.
	 *
	 * @param rootNode root node of the Huffman Tree.
	 * @param codeString string which is recursively populated with prefix code.
	 * 
	 * Create a CodeMap (Key/ Value pair) with character as key and its Huffman code
	 * as value by assigning each symbol with its path from root node to its node,
	 * with left being 0 and right being 1.
	 */
	void generateHuffmanCode(BinNode* rootNode, std::string codeString);

	/** Resets all the attributes for next compression operation.	*/
	void clear();

	/** Frees all heap storage associated with the Huffman Tree.	 */
	void deleteTree(BinNode* node);

	/** Reads entire input file and finds frequency of each unique characters. 
	 *  Populates HashMap<char, int> frequency.
	 */
	void readFrequency();
	

	/** Validates input file path and proceeds on reading frequency 
	 *  @see readFrequency()
	 */
	void scanFile(const fs::path& infilePath);

	/**
	 *  Write the entire Huffman tree in to the file header section 
	 *  using a pre-order traversal algorithm.
	 * 
	 * When we visit a leaf node, write bit 1 followed by the symbol
	 * in 8 bits. And when we visit an internal node (or the root node),
	 * simply write bit 0 only.
	 */
	void writeTree(std::ofstream& writer, BinNode* head);
	
	/**
	 *  Write the header section to compressed file.
	 * 
	 * Header section of compressed file contains tree and other metaData
	 * required during decompression.
	 * Meta data includes number of input files, each file size and file path
	 */
	void writeHeader(const std::string& inputName, std::ofstream& writer);
	
	/**
	 *  Write the body section to compressed file.
	 *
	 * Body section of compressed file contains corresponding prefix code of
	 * each unique characters in the source.
	 * Prefix code are grouped into 8 and its corresponding character code is
	 * written to the file
	 */
	void writeBody(char& chr, int& bufferSize, const std::string& infileName, std::ofstream& writer);
	
	/**
	 *  Write the header and body section to compressed file.
	 *  @see writeHeader()
	 *  @see writeBody()
	 */
	fs::path writeIntoFile(const std::string& infileName);

	/**
	 *  Utility function to compress file.
	 */
	void compress(const std::string& infileName);

public:
	Compressor();
	~Compressor();

	/**
	 *  Compresses a single input file.
	 * 
	 * @param infileName source file path to be compressed.
	 */
	void compressFile(const std::string& infileName);
	
	/**
	 *  Compresses a directory and its entire content recursively.
	 * 
	 * 	@param directoryName source directory path to be compressed.
	 */
	void compressFolder(const std::string& directoryName);
	
	/**
	 *  Compresses multiple source files into single compressed(.huf) file.
	 * 
	 *  @param infileNames list of source files to be compressed.
	 */
	void compressFiles(std::initializer_list<std::string> infileNames);
};