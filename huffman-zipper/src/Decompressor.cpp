#include"Decompressor.h"

Decompressor::~Decompressor() {
	if (remove("./src/binary_temp.tmp") != 0)
		perror("tempFile deletion failed");
	else
		std::cout << "tempFile deleted successfully\n";
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

	//for (auto&& var : codeMap) {
	//	std::cout << var.key << "=" << var.value << std::endl;
	//}
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

BinNode* Decompressor:: buildDecodingTree() {
	BinNode* rootNode = new BinNode(INTERNAL_NODE_CHARACTER);
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
	return rootNode;
}

void Decompressor::decodeCharacters(BinNode* root) {
	std::ofstream outFile(DECOMPRESSED_FILE_PATH, std::ios::out | std::ios::binary | std::ios::trunc);
	if (!outFile)
		throw std::runtime_error("[DECOMPRESSED_FILE] couldn't be opened");

	tempFile.clear();
	tempFile.seekg(0, std::ios::beg);

	char ch;
	BinNode* curr = root;
	while (tempFile.read(reinterpret_cast<char*>(&ch), sizeof(ch))) {
		if (ch == '0')
			curr = curr->getLeftChild();
		else
			curr = curr->getRightChild();

		if (curr->isLeaf()) {		// reached leaf node 
			if (curr->getCharacter() == PSEUDO_EOF) {
				break;
			}
			outFile.put(curr->getCharacter());
			curr = root;
		}
	}

	tempFile.close();
	outFile.flush();
	outFile.close();
}

void Decompressor::decompressor(std::string infileName) {
	auto start = std::chrono::steady_clock::now();
	infile.open(infileName, std::ios::in | std::ios::binary);
	if (!infile)
		throw std::runtime_error("[decompressor, infile] couldn't be opened");

	readAllCharFromFile();
	BinNode* rootNode = buildDecodingTree();
	decodeCharacters(rootNode);
	deleteTree(rootNode);

	auto stop = std::chrono::steady_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);
	std::cout << "Decompression Time: " << duration.count() << " seconds" << std::endl;
}

void Decompressor::deleteTree(BinNode* node) {
	if (node == nullptr) return;

	/* first delete both subtrees */
	deleteTree(node->getLeftChild());
	deleteTree(node->getRightChild());

	/* then delete the node */
	delete node;
}









