#include "Compressor.h"

Compressor::Compressor() :rootNode(nullptr), fileCount(0) {}

Compressor::~Compressor() {
	frequency.clear();
	codeMap.clear();
	deleteTree(rootNode);
}

void Compressor::deleteTree(BinNode* node) {
	if (node == nullptr) return;

	deleteTree(node->getLeftChild());
	deleteTree(node->getRightChild());

	delete node;
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
	int count = 0;
	while (infile.get(ch)) {
		frequency[ch]++;
		count++;
	}
	metaData += std::to_string(count) + FILE_SIZE_SEPARATOR;
}

void Compressor::scanFile(const std::string& infileName) {
	infile.open(infileName, std::ios::in | std::ios::binary);
	if (!infile)
		throw std::runtime_error("Input Error : \'" + infileName + "\' couldn't be opened");
	readFrequency();
	infile.close();
}

void Compressor::scanPath(const std::string& pathName) {
	if (!fs::directory_entry(pathName).is_directory()) {
		scanFile(pathName);

		fileCount++;
		metaData += fs::path(pathName).filename().string() + FILE_NAME_SEPARATOR;
	}
	else {
		for (auto&& entry : fs::recursive_directory_iterator(pathName)) {
			if (entry.is_regular_file()) {
				std::cout << entry.path() << '\n';
				scanFile(entry.path().string());

				fileCount++;
				metaData += fs::relative(entry.path(), pathName).string() + FILE_NAME_SEPARATOR;
			}
		}
	}
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

void Compressor::writeHeader(std::ofstream& outfile) {

	writeTree(outfile, rootNode);

	// Write total number of files
	outfile.write(reinterpret_cast<char*>(&fileCount), sizeof(fileCount));

	// Write total number of characters in each file ,filename and directories
	std::string fileData;
	for (auto&& ch : metaData) {
		fileData += ch;
		if (ch == FILE_SIZE_SEPARATOR) {
			fileData.pop_back();
			int fileSize = std::stoi(fileData);
			outfile.write(reinterpret_cast<char*>(&fileSize), sizeof(fileSize));
			fileData.clear();
		}
		if (ch == FILE_NAME_SEPARATOR) {
			outfile.write(fileData.c_str(), fileData.size());
			fileData.clear();
		}
	}
}

void Compressor::writeBody(char& chr, int& bufferSize, const std::string& infileName, std::ofstream& outfile) {
	infile.open(infileName, std::ios::in | std::ios::binary);
	if (!infile)
		throw std::runtime_error("[compressFiles] one or more files in the directory cant be opened");

	std::cout << "Encoded String for " + infileName + " ... " << std::endl;

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

void Compressor::writeIntoFile(const std::string& inputName, const std::string& outfileName) {
	std::ofstream outfile(outfileName, std::ios::out | std::ios::binary | std::ios::trunc);
	if (!outfile)
		throw std::runtime_error("Output Error : \'" + outfileName + "\' couldn't be created");

	writeHeader(outfile);
	char chr = 0;
	int bufferSize = 8;

	if (!std::filesystem::directory_entry(inputName).is_directory()) {
		writeBody(chr, bufferSize, inputName, outfile);
	}
	else {
		for (auto&& p : std::filesystem::recursive_directory_iterator(inputName)) {
			if (p.is_regular_file()) {
				writeBody(chr, bufferSize, p.path().string(), outfile);
			}
		}
	}

	if (bufferSize) {
		chr = chr << bufferSize;
		outfile.write(reinterpret_cast<char*>(&chr), sizeof(chr));
	}

	outfile.flush();
	outfile.close();
}

void Compressor::compress(const std::string& infileName) {
	std::cout << "Compressing ..." << std::endl;
	auto start = std::chrono::steady_clock::now();

	std::cout << "Reading frequency ..." << std::endl;
	scanPath(infileName);

	std::cout << "Creating Huffman Tree ..." << std::endl;
	rootNode = createHuffmanTree();

	std::cout << "Generating CodeMap ..." << std::endl;
	generateHuffmanCode(rootNode, "");

	std::cout << "Encoding to File ..." << std::endl;
	writeIntoFile(infileName, COMPRESSED_FILE_PATH);

	std::cout << "Success: Compression Completed.\n" << std::endl;

	auto stop = std::chrono::steady_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);
	std::cout << "Compression Time: " << duration.count() << " seconds\n" << std::endl;

	//std::cout << "display Huffman code\n";
	//for (auto&& var : codeMap) {
	//	std::cout << var.key << "=" << var.value << std::endl;
	//}
}

void Compressor::compressFile(const std::string& infileName) {
	if (!std::filesystem::directory_entry(infileName).is_regular_file())
		throw std::runtime_error("ERROR : Please enter a valid file path");

	compress(infileName);
}

void Compressor::compressFolder(const std::string& directoryName) {
	if (!std::filesystem::directory_entry(directoryName).is_directory())
		throw std::runtime_error("ERROR : Please enter a valid directory path");

	compress(directoryName);
}