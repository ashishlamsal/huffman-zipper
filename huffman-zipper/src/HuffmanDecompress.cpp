#include "HuffmanDecompress.h"

HuffmanDecompress::HuffmanDecompress() :rootNode(nullptr) {}

HuffmanDecompress::~HuffmanDecompress() {
	deleteTree(rootNode);
}

void HuffmanDecompress::deleteTree(BinNode* node) {
	if (node == nullptr) return;

	deleteTree(node->getLeftChild());
	deleteTree(node->getRightChild());

	delete node;
}

BinNode* HuffmanDecompress::readTree(std::ifstream& reader) {
	char nodeType;
	reader.get(nodeType);
	if (nodeType == '1') {
		char ch;
		reader.get(ch);
		BinNode* head = new BinNode(ch);
		return head;
	}
	BinNode* head = new BinNode(INTERNAL_NODE_CHARACTER);
	head->setLeftChild(readTree(reader));
	head->setRightChild(readTree(reader));
	return head;
}

void HuffmanDecompress::writeIntoFile(const std::string& outfileName) {
	std::ofstream outfile(outfileName, std::ios::out | std::ios::binary | std::ios::trunc);
	if (!outfile)
		throw std::runtime_error("Output Error : \'" + outfileName + "\' couldn't be created");
	
	rootNode = readTree(infile);
	// Read total number of characters
	int totalChars = 0;
	infile.read(reinterpret_cast<char*>(&totalChars), sizeof(totalChars));
	std::cout << "DeCompression NUM: " << totalChars << std::endl;

	char ch;
	int readChars = 0;
	BinNode* curr = rootNode;
	while (infile.read(reinterpret_cast<char*>(&ch), sizeof(ch)) && readChars != totalChars) {
		for (auto&& binCode : std::bitset<8>(ch).to_string()) {
			if (binCode == '0')
				curr = curr->getLeftChild();
			else if (binCode == '1')
				curr = curr->getRightChild();
			else
				throw std::logic_error("Assertion error: Invalid binary code");

			if (curr->isLeaf()) {
				outfile.put(curr->getCharacter());
				curr = rootNode;

				if (++readChars == totalChars) {
					break;
				}
			}
		}
	}
	std::cout << "DeCompression read: " << readChars << std::endl;

	infile.close();
	outfile.flush();
	outfile.close();

	if (readChars != totalChars)
		throw std::runtime_error("ERROR: Compressed file is corrupted");
}

void HuffmanDecompress::decompressFile(const std::string& infileName) {
	std::cout << "Decompressing ..." << std::endl;
	auto start = std::chrono::steady_clock::now();

	infile.open(infileName, std::ios::in | std::ios::binary);
	if (!infile)
		throw std::runtime_error("Input Error : \'" + infileName + "\' couldn't be opened");

	std::cout << "Decoding Characters ..." << std::endl;
	writeIntoFile(DECOMPRESSED_FILE_PATH1);

	std::cout << "Success : Decompression Completed.\n" << std::endl;

	auto stop = std::chrono::steady_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);
	std::cout << "Decompression Time: " << duration.count() << " seconds\n" << std::endl;
}
