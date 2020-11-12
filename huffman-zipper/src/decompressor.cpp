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
	for (auto var : codeMap) {
		std::cout << var.key << "=" << var.value;
	}
}
void Decompressor::readAllCharFromFile() {
	char character;
	std::string encodedString;
	std::ofstream tempFile("./binary_temp.tmp");
	if (!tempFile) throw std::exception("[binary_temp] couldn't be opened");
	readHeader();
	while (infile.get(character))
	{
		std::bitset<8> bits(character);
		std::cout <<"----"<< character;
		//writes the binary code into the tempFile
		tempFile << bits.to_string();
		
	}
	tempFile.close();
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

void Decompressor::decodeCharacters(BinNode* root) {
	std::ifstream tempFile("./binary_temp.tmp");
	if (!tempFile) throw std::exception("[binary_temp.tmp] couldn't be opened");
	std::ofstream outFile(DECOMPRESSED_FILE_PATH);
	if(!outFile) throw std::exception("[DECOMPRESSED_FILE] couldn't be opened");

	char ch;
	BinNode* curr = root;
	while(1) {
		tempFile.get(ch);
		if ( ch == '0')
			curr = curr->getLeftChild();
		else
			curr = curr->getRightChild();

		// reached leaf node 
		if (curr->getLeftChild() == nullptr && curr->getRightChild() == nullptr) {
			if (curr->getCharacter() == PSEUDO_EOF) {
				tempFile.close();
				return ;
			}
			outFile << curr->getCharacter();
			curr = root;
		}
	}
}




void Decompressor::decompressor(std::string infileName) {	
	infile.open(infileName);
	if (!infile) throw std::exception("[decompressor, infile] couldn't be opened");
		// write the extracted text(in binary) into tempFile
	readAllCharFromFile();
	infile.close();

	BinNode* rootNode = buildDecodingTree();
	std::cout << "test";
	
	decodeCharacters(rootNode);


	

	
}









