#include "HuffmanCompress.h"

HuffmanCompress::HuffmanCompress() :rootNode(nullptr), numChars(0) {}

HuffmanCompress::~HuffmanCompress() {
	deleteTree(rootNode);
}

void HuffmanCompress::deleteTree(BinNode* node) {
	if (node == nullptr) return;

	deleteTree(node->getLeftChild());
	deleteTree(node->getRightChild());

	delete node;
}

//create the Huffman's tree out of frequency map
BinNode* HuffmanCompress::createHuffmanTree() {
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

void HuffmanCompress::generateHuffmanCode(BinNode* rootNode, std::string codeString) {
	if (rootNode == nullptr)
		return;
	if (rootNode->isLeaf()) {
		codeMap[rootNode->getCharacter()] = codeString;
	}

	generateHuffmanCode(rootNode->getLeftChild(), codeString + "0");
	generateHuffmanCode(rootNode->getRightChild(), codeString + "1");
}

void HuffmanCompress::writeTree(std::ofstream& writer, BinNode* head) {
	if (head->isLeaf()) {
		writer.put('1');
		writer.put(head->getCharacter());
		return;
	}
	writer.put('0');
	writeTree(writer, head->getLeftChild());
	writeTree(writer, head->getRightChild());
}

void HuffmanCompress::readFrequency() {
	char ch;
	while (infile.get(ch)) {
		numChars++;
		frequency[ch]++;
	}
}

void HuffmanCompress::writeIntoFile(const std::string& outfileName) {
	std::ofstream outfile(outfileName, std::ios::out | std::ios::binary | std::ios::trunc);
	if (!outfile)
		throw std::runtime_error("Output Error : \'" + outfileName + "\' couldn't be created");

	infile.clear();
	infile.seekg(0, std::ios::beg);

	writeTree(outfile, rootNode);
	outfile.write(reinterpret_cast<char*>(&numChars), sizeof(numChars));
	std::cout << "Compression NUM: " << numChars << std::endl;

	char ch;
	char chr = 0;
	int bufferSize = 8;
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

	if (bufferSize) {
		chr = chr << bufferSize;
		outfile.write(reinterpret_cast<char*>(&chr), sizeof(chr));
	}

	infile.close();
	outfile.flush();
	outfile.close();
}

void HuffmanCompress::compressFile(const std::string& infileName) {
	std::cout << "Compressing ..." << std::endl;
	auto start = std::chrono::steady_clock::now();

	infile.open(infileName, std::ios::in | std::ios::binary);
	if (!infile)
		throw std::runtime_error("Input Error : \'" + infileName + "\' couldn't be opened");

	std::cout << "Reading frequency ..." << std::endl;
	readFrequency();

	std::cout << "Creating Huffman Tree ..." << std::endl;
	rootNode = createHuffmanTree();

	std::cout << "Generating CodeMap ..." << std::endl;
	generateHuffmanCode(rootNode, "");

	std::cout << "Encoding to File ..." << std::endl;
	writeIntoFile(COMPRESSED_FILE_PATH1);

	std::cout << "Success: Compression Completed.\n" << std::endl;

	auto stop = std::chrono::steady_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);
	std::cout << "Compression Time: " << duration.count() << " seconds\n" << std::endl;

	//std::cout << "display Huffman code\n";
	//for (auto&& var : codeMap) {
	//	std::cout << var.key << "=" << var.value << std::endl;
	//}
}