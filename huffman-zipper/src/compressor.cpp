#include<iostream>
#include<fstream>
#include<sstream>
#include<bitset>
#include<unordered_map>
#include<queue>
#define INTERNAL_NODE_CHARACTER char(128)
#define PSEUDO_EOF char(129)
#define CHARACTER_CODE_SEPERATOR char(130)
#define HEADER_ENTRY_SEPERATOR char(131)
#define HEADER_TEXT_SEPERATOR char(132)

#include"BinNode.h"

class Comparator {
public:
	bool operator()(BinNode* first, BinNode* second) {
		return first->getFrequency() > second->getFrequency();
		// to adjust in the ascending order i.e min-heap
	}
};

std::unordered_map<char,int> getFrequency(std::ifstream & infile) {
	char ch;
	std::unordered_map<char, int> frequency;
	while (!infile.eof()) { // inline.get(c) 
		infile.get(ch);
		frequency[ch]++;
	}
	frequency[PSEUDO_EOF]++;
	infile.close();

	for (auto&& character : frequency)
		std::cout << (int)character.first << "=" << character.second << std::endl;

	return frequency;
}

BinNode* createHuffmanTree(std::unordered_map<char, int> frequency) {
	//takes frequency count and return the pointer to root node of huffman tree

	std::priority_queue<BinNode*, std::vector<BinNode*>, Comparator> pq;
	for (auto&& character : frequency) {
		pq.push(new BinNode(character.first, character.second));
	}

	std::cout << "Building Tree...\n";
	while (pq.size() != 1)
	{
		BinNode* left = pq.top();
		pq.pop();
		BinNode* right = pq.top();
		pq.pop();
		BinNode* new_pair = new BinNode('$', left->getFrequency() + right->getFrequency());
		pq.push(new_pair);
		new_pair->setLeftChild(left);
		new_pair->setRightChild(right);
	}
	return pq.top();
}

void generateHuffmanCode(BinNode* rootNode, std::string codeString, std::unordered_map<char, std::string>& codeMap) {
	if (rootNode == nullptr)
		return;
	if (rootNode->getLeftChild() == nullptr && rootNode->getRightChild() == nullptr) {
		codeMap[rootNode->getCharacter()] = codeString;
	}

	generateHuffmanCode(rootNode->getLeftChild(), codeString + "0",codeMap);
	generateHuffmanCode(rootNode->getRightChild(), codeString + "1",codeMap);

}

void writeHeader(std::ofstream &outfile, std::unordered_map<char, std::string>codeMap) {
	for (const auto& item : codeMap)
		outfile << item.first << CHARACTER_CODE_SEPERATOR << item.second << HEADER_ENTRY_SEPERATOR;
	outfile << HEADER_TEXT_SEPERATOR;

}
void encodeIntoFile(std::string encodedString, std::string outfileName, std::unordered_map<char, std::string>codeMap) {
	std::ofstream outfile("./src/" + outfileName);;
	if (!outfile) {
		std::cout << "Error writing on the file";
		exit(1);
	}

	writeHeader(outfile,codeMap);
	//mark pseudo end of the file
	encodedString += codeMap[PSEUDO_EOF];
	unsigned long remainder = (encodedString.size()) % 8;
	for (int i = 0; i < 8 - remainder; ++i)
		encodedString += '0';
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

std::string generateEncodedString(std::unordered_map<char, std::string> codeMap, std::ifstream& infile) {

	char character;
	std::string encodedString;
	//write the header to the encoded string 


	// seek the pointer to the beginning of the file
	// temporary fix; // will fix permanently once internet available
	
	infile.close();
	infile.open("./src/small-text.txt");

	while (infile.get(character)) {
		encodedString += codeMap[character];
	}

	return encodedString;
}


void compressor(std::string infileName) {
	std::ifstream infile("./src/"+infileName);
	if (!infile) {
		std::cout << "Error: File couldn't be opened." << std::endl;
		exit(1);
	}
	std::cout << "Success: File opened successfully." << std::endl;

	std::unordered_map<char, int> frequency = getFrequency(infile);
	//create the huffmantree out of frequency map

	BinNode* rootNode = createHuffmanTree(frequency);
	
	std::unordered_map<char, std::string> codeMap;
	generateHuffmanCode(rootNode, "",codeMap);
	//display the huffman code
	std::cout << "display huffman code\n";
	for (auto&& code : codeMap)
		std::cout <<code.first << "=" << code.second << std::endl;

	//generate the encodedString from the file.
	std::string encodedString = generateEncodedString(codeMap,infile);


	encodeIntoFile(encodedString, "output.txt",codeMap);

	infile.close();

}


