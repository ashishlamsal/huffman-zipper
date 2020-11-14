#include "Compressor.h"

HashMap<char, int> Compressor::getFrequency() {
	char ch;
	while (!infile.eof()) {
		infile.get(ch);
		frequency[ch]++;
	}
	frequency[PSEUDO_EOF]++;
	return frequency;
}

//create the Huffman's tree out of frequency map
BinNode* Compressor::createHuffmanTree() {
	PriorityQueue<BinNode*> pq;
	for (auto&& character : frequency) {
		pq.enqueue(new BinNode(character.key, character.value));
	}

	//std::cout << "Building Tree...\n";
	while (pq.getSize() != 1)
	{
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

std::string Compressor::generateEncodedString() {
	char ch;
	std::string encodedString;

	infile.clear();
	infile.seekg(0, std::ios::beg);

	while (infile.get(ch)) {
		encodedString += codeMap[ch];
	}
	infile.close();

	return encodedString;
}

//write the header to the encoded string 
void Compressor::writeHeader(std::ofstream& outfile) {
	for (const auto& item : codeMap) {
		outfile << item.key << CHARACTER_CODE_SEPERATOR << item.value << HEADER_ENTRY_SEPERATOR;
	}
	outfile << HEADER_TEXT_SEPERATOR;
}

void Compressor::encodeIntoFile(std::string encodedString, std::string outfileName) {
	std::ofstream outfile(outfileName, std::ios::out | std::ios::binary | std::ios::trunc);
	if (!outfile) {
		std::cout << "Error writing on the file";
		exit(1);
	}

	writeHeader(outfile);

	//mark pseudo end of the file
	encodedString += codeMap[PSEUDO_EOF];

	unsigned long remainder = (encodedString.size()) % 8;
	if (remainder) {
		for (int i = 0; i < 8 - remainder; ++i)
			encodedString += '0';
	}

	std::stringstream stringStream(encodedString);
	while (stringStream.good()) {
		std::bitset<8> bits;
		stringStream >> bits;
		char c = char(bits.to_ulong());
		//std::cout << c;
		outfile.write(reinterpret_cast<char*>(&c), sizeof(c));
	}
	outfile.flush();
	outfile.close();
}

void Compressor::compressor(std::string infileName) {
	auto start = std::chrono::steady_clock::now();

	infile.open(infileName);
	if (!infile) {
		std::cout << "Error: File couldn't be opened." << std::endl;
		exit(1);
	}
	std::cout << "Success: File opened successfully." << std::endl;

	HashMap<char, int> frequency = getFrequency();
	BinNode* rootNode = createHuffmanTree();
	generateHuffmanCode(rootNode, "");
	deleteTree(rootNode);
	std::string encodedString = generateEncodedString();
	encodeIntoFile(encodedString, COMPRESSED_FILE_PATH);

	auto stop = std::chrono::steady_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);
	std::cout << "Compression Time: " << duration.count() << " seconds" << std::endl;

	////display the Huffman code
	//std::cout << "display Huffman code\n";
	//for (auto&& var : codeMap) {
	//	std::cout << var.key << "=" << var.value << std::endl;
	//}
}

void Compressor::deleteTree(BinNode* node) {
	if (node == nullptr) return;

	/* first delete both subtrees */
	deleteTree(node->getLeftChild());
	deleteTree(node->getRightChild());

	/* then delete the node */
	delete node;
}