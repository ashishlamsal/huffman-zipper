#include"Decompressor.h"




void Decompressor::readHeader() {
	char c;
	infile.get(c);
	char key = c;
	while (c != HEADER_TEXT_SEPERATOR) {

		if (c == CHARACTER_CODE_SEPERATOR) {
			infile.get(c);
			while (c != HEADER_ENTRY_SEPERATOR) {
				std::cout << c;
				codeMap[key] += c;
				infile.get(c);
			}
		}
		else
			key = c;
		infile.get(c);
	}
}
std::string Decompressor::readAllCharFromFile() {
	char character;
	std::string encodedString;
	readHeader();
	while (infile.get(character))
	{
		std::bitset<8> bits(character);
		std::cout <<"----"<< character;
		encodedString += bits.to_string();
		
	}

	return encodedString;
}

std::string Decompressor::extractTextFromFile() {
	std::string encodedString;

	encodedString = readAllCharFromFile();
	return encodedString;

}


BinNode* Decompressor:: buildDecodingTree() {

	BinNode* rootNode = new BinNode(INTERNAL_NODE_CHARACTER, int());
	BinNode* previousNode;

	for (auto&& item : codeMap) {
		previousNode = rootNode;
		std::string& characterCode = item.value;
		for (int i = 0; i < characterCode.size(); i++) {
			if (characterCode[i] == '0') {
				if (i == characterCode.size() - 1)		// last character
					previousNode->setLeftChild(new BinNode(item.key, int()));
				else {
					if (!previousNode->getLeftChild())
						previousNode->setLeftChild(new BinNode(INTERNAL_NODE_CHARACTER, int()));
					previousNode = previousNode->getLeftChild();
				}
			}
			else {
				if (i == characterCode.size() - 1)
					previousNode->setRightChild(new BinNode(item.key, int()));
				else {
					if (!previousNode->getRightChild())
						previousNode->setRightChild(new BinNode(INTERNAL_NODE_CHARACTER, int()));
					previousNode = previousNode->getRightChild();
				}
			}
		}
	}
	return rootNode;
}

std::string Decompressor::decodeCharacters(BinNode* root, std::string encodedString) {
	std::string decodedString = "";
	BinNode* curr = root;
	for (int i = 0; i < encodedString.size(); i++) {
		if (encodedString[i] == '0')
			curr = curr->getLeftChild();
		else
			curr = curr->getRightChild();

		// reached leaf node 
		if (curr->getLeftChild() == nullptr && curr->getRightChild() == nullptr) {
			if (curr->getCharacter() == PSEUDO_EOF) return decodedString;
			decodedString += curr->getCharacter();
			curr = root;
		}
	}
	//return decodedString;
}

void Decompressor::writeIntoFile(const std::string& decodedString) {
	std::cout << "decoding tree";
	std::ofstream outfile(DECOMPRESSED_FILE_PATH);
	
	outfile << decodedString;
	outfile.close();

}


void Decompressor::decompressor(std::string infileName) {	
	infile.open(infileName);
	std::string encodedString = extractTextFromFile();
	std::cout <<"DE-ENCODEDSTRING\n"<< encodedString;
	std::cout << "DE-encoding\n";
	infile.close();

	BinNode* rootNode = buildDecodingTree();
	
	std::string decodedString= decodeCharacters(rootNode, encodedString);
	
	std::cout << decodedString;
	writeIntoFile(decodedString);
	std::cout << "decoding tree";



	// decoding tree 

	// final code 

	
}









