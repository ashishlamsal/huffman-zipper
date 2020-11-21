#include "Compressor.h"

Compressor::Compressor() :rootNode(nullptr) {}

Compressor::~Compressor() {
	deleteTree(rootNode);
}

void Compressor::deleteTree(BinNode* node) {
	if (node == nullptr) return;

	deleteTree(node->getLeftChild());
	deleteTree(node->getRightChild());

	delete node;
}

void Compressor::getFrequency() {
	char ch;
	while (infile.get(ch)) {
		//std::cout <<"[getFrequency()]"<< ch<<std::endl;
		frequency[ch]++;
	}
	frequency[FILE_SEPARATOR]++;
}

//create the Huffman's tree out of frequency map
BinNode* Compressor::createHuffmanTree() {
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

void Compressor::generateHuffmanCode(BinNode* rootNode, std::string codeString) {
	if (rootNode == nullptr)
		return;
	if (rootNode->isLeaf()) {
		codeMap[rootNode->getCharacter()] = codeString;
	}

	generateHuffmanCode(rootNode->getLeftChild(), codeString + "0");
	generateHuffmanCode(rootNode->getRightChild(), codeString + "1");
}

void Compressor::generateEncodedString() {
	char ch;
	
	infile.clear();
	infile.seekg(0, std::ios::beg);

	while (infile.get(ch)) {
		encodedString += codeMap[ch];
	}

	//mark pseudo end of the file
	encodedString += codeMap[FILE_SEPARATOR];
	
	infile.close();
}

//write the header to the encoded string 
void Compressor::writeHeader(std::ofstream& outfile) {
	for (const auto& item : codeMap) {
		outfile << item.key << CHARACTER_CODE_SEPERATOR << item.value << HEADER_ENTRY_SEPERATOR;
	}
	outfile << HEADER_TEXT_SEPERATOR;
}

void Compressor::encodeIntoFile(const std::string& outfileName) {
	std::ofstream outfile(outfileName, std::ios::out | std::ios::binary | std::ios::trunc);
	if (!outfile)
		throw std::runtime_error("Output Error : \'" + outfileName + "\' couldn't be created");

	writeHeader(outfile);

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

void Compressor::compressFile(const std::string& infileName) {
	std::cout << "Compressing ..." << std::endl;
	auto start = std::chrono::steady_clock::now();

	infile.open(infileName, std::ios::in | std::ios::binary);
	if (!infile)
		throw std::runtime_error("Input Error : \'" + infileName + "\' couldn't be opened");
	
	std::cout << "Reading frequency ..." << std::endl;
	getFrequency();
	
	std::cout << "Creating Huffman Tree ..." << std::endl;
	rootNode = createHuffmanTree();
	
	std::cout << "Generating CodeMap ..." << std::endl;
	generateHuffmanCode(rootNode, "");
	
	std::cout << "Generating Encoded String ..." << std::endl;
	generateEncodedString();
	
	std::cout << "Encoding to File ..." << std::endl;
	encodeIntoFile(COMPRESSED_FILE_PATH);
	
	std::cout << "Success: Compression Completed.\n" << std::endl;

	auto stop = std::chrono::steady_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);
	std::cout << "Compression Time: " << duration.count() << " seconds\n" << std::endl;

	std::cout << "display Huffman code\n";
	for (auto&& var : codeMap) {
		std::cout << var.key << "=" << var.value << std::endl;
	}
}

void Compressor::compressFiles(const std::string& directoryName) {
	std::cout << "Compressing ..." << std::endl;
	auto start = std::chrono::steady_clock::now();
	for (auto& p : std::filesystem::directory_iterator(directoryName))
	{
		std::cout << p.path() << '\n';
		infile.open(p.path(), std::ios::in | std::ios::binary);
		if (!infile)
			throw std::exception("[compressFiles] one or more files in the directory cant be opened");
		std::cout << "Reading frequency ..." << std::endl;
		char ch;
		/*while (infile.get(ch))
		{

			std::cout << ch;
		}*/
		getFrequency();
		infile.close();
		
	}
	frequency[PSEUDO_EOF]++;
	std::cout << "Creating Huffman Tree ..." << std::endl;
	rootNode = createHuffmanTree();
	std::cout << "Generating CodeMap ..." << std::endl;
	generateHuffmanCode(rootNode, "");

	for (auto& p : std::filesystem::directory_iterator(directoryName))
	{
		infile.open(p.path(), std::ios::in | std::ios::binary);
		if (!infile)
			throw std::exception("[compressFiles] one or more files in the directory cant be opened");
		std::cout << "Generating Encoded String for " + p.path().string() + " ... " << std::endl;
		generateEncodedString();
	}
	encodedString += codeMap[PSEUDO_EOF];

	std::cout << "Encoding to File ..." << std::endl;
	encodeIntoFile(COMPRESSED_FILE_PATH);
	std::cout << "Success: Compression Completed.\n" << std::endl;
	auto stop = std::chrono::steady_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);
	std::cout << "Compression Time: " << duration.count() << " seconds\n" << std::endl;

	std::cout << "display Huffman code\n";
	for (auto&& var : codeMap) {
		std::cout << var.key << "=" << var.value << std::endl;
	}
	/*std::ifstream infile("./src/test/test.txt");
	char ch;
	while (infile.get(ch))
			{
				
				std::cout << ch;
			}*/
}

void Compressor::compressFolder(const std::string& infileName) {

}
