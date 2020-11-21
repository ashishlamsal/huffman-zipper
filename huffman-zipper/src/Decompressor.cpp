#include "Decompressor.h"

Decompressor::Decompressor() :rootNode(nullptr) {}

Decompressor::~Decompressor() {
	deleteTree(rootNode);

	if (remove("./src/binary_temp.tmp") != 0)
		perror("tempFile deletion failed");
	else
		std::cout << "tempFile deleted successfully\n";
}

void Decompressor::deleteTree(BinNode* node) {
	if (node == nullptr) return;

	deleteTree(node->getLeftChild());
	deleteTree(node->getRightChild());

	delete node;
}

void Decompressor::readHeader() {
	char ch;
	infile.read(reinterpret_cast<char*>(&ch), sizeof(ch));
	char key = ch;
	while (ch != HEADER_TEXT_SEPERATOR) {
		if (ch == CHARACTER_CODE_SEPERATOR) {
			infile.read(reinterpret_cast<char*>(&ch), sizeof(ch));
			while (ch != HEADER_ENTRY_SEPERATOR) {
				codeMap[key] += ch;
				infile.read(reinterpret_cast<char*>(&ch), sizeof(ch));
			}
		}
		else {
			key = ch;
		}
		infile.read(reinterpret_cast<char*>(&ch), sizeof(ch));
	}

	for (auto&& var : codeMap) {
		std::cout << var.key << "=" << var.value << std::endl;
	}
}

void Decompressor::readAllCharFromFile() {
	tempFile.open("./src/binary_temp.tmp", std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);
	if (!tempFile)
		throw std::runtime_error("[binary_temp] couldn't be opened");

	readHeader();

	char ch;
	while (infile.read(reinterpret_cast<char*>(&ch), sizeof(ch))) {
		//std::cout << ch;
		std::bitset<8> bits(ch);
		// write the extracted binary code into tempFile
		tempFile.write(bits.to_string().c_str(), bits.size());
	}
	//std::cout << std::endl;
	infile.close();
}

void Decompressor:: buildDecodingTree() {
	rootNode = new BinNode(INTERNAL_NODE_CHARACTER);
	BinNode* previousNode;

	for (auto&& item : codeMap) {
		previousNode = rootNode;
		std::string& characterCode = item.value;
		for (int i = 0; i < characterCode.size(); i++) {
			if (characterCode[i] == '0') {
				if (i == characterCode.size() - 1)		// last character
					previousNode->setLeftChild(new BinNode(item.key));
				else {
					if (!previousNode->getLeftChild())
						previousNode->setLeftChild(new BinNode(INTERNAL_NODE_CHARACTER));
					previousNode = previousNode->getLeftChild();
				}
			}
			else {
				if (i == characterCode.size() - 1)
					previousNode->setRightChild(new BinNode(item.key));
				else {
					if (!previousNode->getRightChild())
						previousNode->setRightChild(new BinNode(INTERNAL_NODE_CHARACTER));
					previousNode = previousNode->getRightChild();
				}
			}
		}
	}
}

void Decompressor::decodeCharacters(const std::string& outfileName) {
	outfile.open(outfileName, std::ios::out | std::ios::binary | std::ios::trunc);
	if (!outfile)
		throw std::runtime_error("Output Error : \'" + outfileName + "\' couldn't be created");

	tempFile.clear();
	tempFile.seekg(0, std::ios::beg);
	int count = 1;
	char ch;
	BinNode* curr = rootNode;
	while (tempFile.read(reinterpret_cast<char*>(&ch), sizeof(ch))) {
		if (ch == '0')
			curr = curr->getLeftChild();
		else if (ch == '1')
			curr = curr->getRightChild();
		else
			throw std::logic_error("Assertion error: Invalid binary code");

		if (curr->isLeaf()) {		// reached leaf node 
			if (curr->getCharacter() == PSEUDO_EOF) {
				break;
			}
			if (curr->getCharacter() == FILE_SEPARATOR) {

				outfile.flush();
				outfile.close();


				outfile.open(std::string(outfileName).insert(outfileName.find_last_of("."),std::to_string(++count)), std::ios::out | std::ios::binary | std::ios::trunc);
				if (!outfile) throw std::exception("Decompressing file couldnt be opened");
				curr = rootNode;
				continue;
			}
			
			outfile.put(curr->getCharacter());
			curr = rootNode;
		}
	}

	tempFile.close();
	outfile.flush();
	outfile.close();
	if (remove(std::string(outfileName).insert(outfileName.find_last_of("."), std::to_string(count)).c_str()))
	{
		throw std::exception("[At decoingcharacter()] Unwanted decompressed file couldn't be deleted");
	}
}

void Decompressor::decompressFile(const std::string& infileName) {
	std::cout << "Decompressing ..." << std::endl;
	auto start = std::chrono::steady_clock::now();

	infile.open(infileName, std::ios::in | std::ios::binary);
	if (!infile)
		throw std::runtime_error("Input Error : \'" + infileName + "\' couldn't be opened");

	std::cout << "Reading Characters from file ..." << std::endl;
	readAllCharFromFile();
	
	std::cout << "Building Decoding Tree ..." << std::endl;
	buildDecodingTree();
	
	std::cout << "Decoding Characters ..." << std::endl;
	decodeCharacters(DECOMPRESSED_FILE_PATH);
	
	std::cout << "Success : Decompression Completed.\n" << std::endl;

	auto stop = std::chrono::steady_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);
	std::cout << "Decompression Time: " << duration.count() << " seconds\n" << std::endl;
}










