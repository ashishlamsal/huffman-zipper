#include "Compressor.h"

Compressor::Compressor() :rootNode(nullptr) {}

Compressor::~Compressor() {
	//clear();
}

void Compressor::deleteTree(BinNode* node) {
	if (node == nullptr) return;

	deleteTree(node->getLeftChild());
	deleteTree(node->getRightChild());

	delete node;
}

void Compressor::clear() {
	frequency.clear();
	codeMap.clear();
	inputFiles.clear();
	deleteTree(rootNode);
	rootNode = nullptr;
}

/// create the Huffman's tree out of frequency map
BinNode* Compressor::createHuffmanTree() {
	PriorityQueue<BinNode*> pq;
	for (auto&& character : frequency) {
		pq.enqueue(new BinNode(character.key, character.value));
	}

	while (pq.getSize() != 1) {
		BinNode* left = pq.dequeue();
		BinNode* right = pq.dequeue();
		BinNode* new_pair = new BinNode(INTERNAL_NODE_CHARACTER, left->getFrequency() + right->getFrequency());
		pq.enqueue(new_pair);
		new_pair->setLeftChild(left);
		new_pair->setRightChild(right);
	}
	return pq.top();
}

void Compressor::generateHuffmanCode(BinNode* rootNode, std::string codeString) {
	if (rootNode == nullptr)
		return;
	if (rootNode->isLeaf()) {
		codeMap[rootNode->getCharacter()] = codeString;
	}

	generateHuffmanCode(rootNode->getLeftChild(), codeString + "0");
	generateHuffmanCode(rootNode->getRightChild(), codeString + "1");
}

void Compressor::readFrequency() {
	char ch;
	while (infile.get(ch)) {
		frequency[ch]++;
	}
}

void Compressor::scanFile(const fs::path& infilePath) {
	infile.open(infilePath, std::ios::in | std::ios::binary);
	if (!infile)
		throw std::runtime_error("Input Error : \'" + infilePath.string() + "\' couldn't be opened");
	readFrequency();
	infile.close();
}

void Compressor::writeTree(std::ofstream& writer, BinNode* head) {
	if (head->isLeaf()) {
		writer.put('1');
		writer.put(head->getCharacter());
		return;
	}
	writer.put('0');
	writeTree(writer, head->getLeftChild());
	writeTree(writer, head->getRightChild());
}

void Compressor::writeHeader(const std::string& inputName, std::ofstream& outfile) {
	writeTree(outfile, rootNode);

	// Write total number of files
	uint16_t fileCount = inputFiles.size();
	outfile.write(reinterpret_cast<char*>(&fileCount), sizeof(fileCount));

	// Write total number of characters in each file, filename and directories
	std::string file_path;
	for (auto&&  file : inputFiles) {
		unsigned int fileSize = fs::file_size(file);
		outfile.write(reinterpret_cast<char*>(&fileSize), sizeof(fileSize));

		if (fs::is_directory(inputName))
			file_path = fs::relative(file, inputName).string();
		else
			file_path = file.filename().string();
		
		outfile.write(file_path.c_str(), file_path.size());
		outfile.put(FILE_NAME_SEPARATOR);
	}
}

void Compressor::writeBody(char& chr, int& bufferSize, const std::string& infileName, std::ofstream& outfile) {
	infile.open(infileName, std::ios::in | std::ios::binary);
	if (!infile)
		throw std::runtime_error("[compressFiles] one or more files in the directory cant be opened");

	char ch;
	while (infile.get(ch)) {
		for (auto&& binCode : codeMap.get(ch)) {
			chr = (chr << 1) ^ (binCode - '0');
			bufferSize--;
			if (bufferSize == 0) {
				outfile.write(reinterpret_cast<char*>(&chr), sizeof(chr));
				chr = 0;
				bufferSize = 8;
			}
		}
	}
	infile.close();
}

fs::path Compressor::writeIntoFile(const std::string& inputName) {
	fs::path outfilePath = fs::canonical(inputName).replace_extension(".huf");
	if (fs::path(inputName) == outfilePath) {
		outfilePath.replace_filename(outfilePath.stem().string() + "_1.huf");
	}
	std::ofstream outfile(outfilePath, std::ios::out | std::ios::binary | std::ios::trunc);
	if (!outfile)
		throw std::runtime_error("Output Error : compressed file couldn't be created");

	writeHeader(inputName, outfile);
	char chr = 0;
	int bufferSize = 8;

	for (auto&& file : inputFiles) {
		writeBody(chr, bufferSize, file.string(), outfile);
	}

	if (bufferSize) {
		chr = chr << bufferSize; /// possibility of extra 8-bits
		outfile.write(reinterpret_cast<char*>(&chr), sizeof(chr));
	}

	outfile.flush();
	outfile.close();

	return outfilePath;
}

void Compressor::compress(const std::string& infileName) {
	std::cout << "Huffman Compression\n";
	std::cout << std::string(19, char(205)) << std::endl;
	std::cout << inputFiles.size() << " file(s) detected\n";

	int fieldWidth = 0;
	int totalSize = 0;
	for (auto&& file : inputFiles) {
		int fileNameWidth = file.filename().string().length() + 3;
		if (fileNameWidth > fieldWidth)
			fieldWidth = fileNameWidth;
		totalSize += fs::file_size(file);
	}
	
	for (auto&& file : inputFiles) {
		std::cout << "Filename : "<<std::setw(fieldWidth) << std::left << file.filename() << " | size: " << fs::file_size(file) << " bytes"<< std::endl;
	}

	std::cout << "\nCompressing ..." << std::endl;
	auto start = std::chrono::steady_clock::now();

	std::cout << "Reading frequency ..." << std::endl;
	for (auto&& file : inputFiles) {
		scanFile(file);
	}

	std::cout << "Creating Huffman Tree ..." << std::endl;
	rootNode = createHuffmanTree();

	std::cout << "Generating CodeMap ..." << std::endl;
	generateHuffmanCode(rootNode, "");

	std::cout << "Encoding to File ..." << std::endl;
	const fs::path& outfilePath = writeIntoFile(infileName);

	std::cout << "Cleaning Up ..." << std::endl;
	clear();
	
	std::cout << "Success: Compression Completed.\n" << std::endl;
	std::cout << "Compressed File Name\n" << outfilePath.filename() << std::endl;
	std::cout << "Compressed File Location\n" << "\"" << outfilePath.parent_path().string() << "\"\n" << std::endl;

	auto stop = std::chrono::steady_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);
	
	int outputSize = fs::file_size(outfilePath);
	std::cout << std::setw(22) << "Total Input Size" << " = "<< totalSize << " bytes" << std::endl;
	std::cout << std::setw(22) << "Compressed File Size" << " = " << outputSize << " bytes" << std::endl;
	std::cout << std::setw(22) << "Compression Ratio" << " = " << std::setprecision(4) << float(totalSize - outputSize) / totalSize * 100 << " % " << std::endl;
	std::cout << std::setw(22) << "Compression Time" << " = " << duration.count() << " seconds\n" << std::endl;
}

void Compressor::compressFile(const std::string& infileName) {
	if (!fs::is_regular_file(infileName))
		throw std::runtime_error("ERROR : Please enter a valid file path");
	
	inputFiles.emplace_back(infileName);
	
	compress(infileName); 
}

void Compressor::compressFolder(const std::string& directoryName) {
	if (!fs::is_directory(directoryName))
		throw std::runtime_error("ERROR : Please enter a valid directory path");

	for (auto&& entry : fs::recursive_directory_iterator(directoryName)) {
		if (entry.is_regular_file()) {
			inputFiles.emplace_back(entry.path());
		}
	}
	
	compress(directoryName);
}

void Compressor::compressFiles(std::initializer_list<std::string> infileNames) {
	for (auto&& infileName : infileNames) {
		if (fs::is_regular_file(infileName))
			inputFiles.emplace_back(infileName);
		else
			throw std::runtime_error("ERROR : Please enter a valid file path");
	}

	compress(inputFiles.front().string());
}

