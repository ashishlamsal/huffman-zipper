#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <string>
#include <sstream>
#include <bitset>

#include "BinNode.h"
#include "Compressor.h"
#include "Decompressor.h"
//#include "PriorityQueue.h"
//#include "MinHeap.h"







std::string decodeCharacters(BinNode* root, std::string encodedString) {
	std::string decodedString = "";
	BinNode* curr = root;
	for (int i = 0; i < encodedString.size(); i++) {
		if (encodedString[i] == '0')
			curr = curr->getLeftChild();
		else
			curr = curr->getRightChild();

		// reached leaf node 
		if (curr->getLeftChild() == nullptr && curr->getRightChild() == nullptr) {
			decodedString += curr->getCharacter();
			curr = root;
		}
	}
	return decodedString;
}



int main() {
	compressor("small-text.txt");

	//encoded string :encode  .txt of file
	/*char character;
	std::string encodedString;
	std::ifstream inputStream("./src/small-text.txt");
	while (inputStream.get(character))
		encodedString += codeMap[character];
	encodedString += codeMap[PSEUDO_EOF];
	inputStream.close();
	std::cout << encodedString << std::endl;

	//decoded string
	std::cout << decodeCharacters(pq.top(), encodedString);
	//TODO
	// 1. Write encodedString to file
	encodeIntoFile(encodedString, "output.txt");


	//-----------------------Decompression-------------------------//
	// 2. Read encodedString from file
	std::string encodedString2 = readEncodedFile("output.txt");
	*/
	
	// 3. Build decoding tree

	// 4. decode string
	// 5. write decoded string to file

	

	return 0;
};