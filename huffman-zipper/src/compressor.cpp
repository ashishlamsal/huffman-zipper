
#include "Compressor.h"




HashMap<char, int>  Compressor::getFrequency() {
	char ch;	
	while (!infile.eof()) { // inline.get(c) 
		infile.get(ch);
		frequency[ch]++;
	}
	frequency[PSEUDO_EOF]++;
	infile.close();
	return frequency;
}

BinNode* Compressor::createHuffmanTree() {
	//takes frequency count and return the pointer to root node of huffman tree

	PriorityQueue<BinNode*> pq;
	for (auto&& character : frequency) {
		pq.enqueue(new BinNode(character.key, character.value));
	}

	std::cout << "Building Tree...\n";
	while (pq.getSize() != 1)
	{
		BinNode* left = pq.dequeue();
		BinNode* right = pq.dequeue();
		BinNode* new_pair = new BinNode('$', left->getFrequency() + right->getFrequency());
		pq.enqueue(new_pair);
		new_pair->setLeftChild(left);
		new_pair->setRightChild(right);
	}
	return pq.top();
}

void Compressor::generateHuffmanCode(BinNode* rootNode, std::string codeString) {
	if (rootNode == nullptr)
		return;
	if (rootNode->getLeftChild() == nullptr && rootNode->getRightChild() == nullptr) {
		codeMap[rootNode->getCharacter()] = codeString;
	}

	generateHuffmanCode(rootNode->getLeftChild(), codeString + "0");
	generateHuffmanCode(rootNode->getRightChild(), codeString + "1");

}

void Compressor::writeHeader(std::ofstream& outfile) {
	for (const auto& item : codeMap)
		outfile << item.key << CHARACTER_CODE_SEPERATOR << item.value << HEADER_ENTRY_SEPERATOR;
	outfile << HEADER_TEXT_SEPERATOR;

}
void Compressor::encodeIntoFile(std::string encodedString, std::string outfileName ) {
	std::ofstream outfile(outfileName);;
	if (!outfile) {
		std::cout << "Error writing on the file";
		exit(1);
	}

	writeHeader(outfile);
	//mark pseudo end of the file
	encodedString += codeMap[PSEUDO_EOF];
	unsigned long remainder = (encodedString.size()) % 8;
	if (remainder){
		for (int i = 0; i < 8 - remainder; ++i)
			encodedString += '1';
	}

	
	
	std::stringstream stringStream(encodedString);

	while (stringStream.good()) {
		std::bitset<8> bits;
		stringStream >> bits;
		char c = char(bits.to_ulong());
		std::cout  << c;
		outfile << c;
	}
	outfile.flush();
	outfile.close();
}

std::string Compressor::generateEncodedString() {

	char character;
	std::string encodedString;
	//write the header to the encoded string 

	
	// seek the pointer to the beginning of the file
	// temporary fix; // will fix permanently once internet available
	
	//infile.seekg(0, std::ios::beg );

	infile.close();
	infile.open(INPUT_FILE_PATH);

	while (infile.get(character)) {
		encodedString += codeMap[character];
	}

	return encodedString;
}


void Compressor::compressor(std::string infileName) {
	infile.open(infileName);
	if (!infile) {
		std::cout << "Error: File couldn't be opened." << std::endl;
		exit(1);
	}
	std::cout << "Success: File opened successfully." << std::endl;

	HashMap<char, int> frequency = getFrequency();
	//create the huffmantree out of frequency map

	BinNode* rootNode = createHuffmanTree();
	
	
	generateHuffmanCode(rootNode, "");
	//display the huffman code
	std::cout << "display huffman code\n";
	for (auto var : codeMap) {
		std::cout << var.key << "==" << var.value << std::endl;
	}
	//generate the encodedString from the file.
	std::string encodedString = generateEncodedString();
	std::cout << "ENCODEDSTRING\n" << encodedString;

	encodeIntoFile(encodedString, COMPRESSED_FILE_PATH);

	infile.close();

}


