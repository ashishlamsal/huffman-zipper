#include "Decompressor.h"

Decompressor::Decompressor() :rootNode(nullptr) {}

Decompressor::~Decompressor() {
	clear();
}

void Decompressor::clear() {
	files.clear();
	deleteTree(rootNode);
	rootNode = nullptr;
}

void Decompressor::deleteTree(BinNode* node) {
	if (node == nullptr) return;

	deleteTree(node->getLeftChild());
	deleteTree(node->getRightChild());

	delete node;
}

BinNode* Decompressor::readTree(std::ifstream& reader) {
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

void Decompressor::readHeader(const std::string& infileName, std::ifstream& infile) {
	rootNode = readTree(infile);

	// Read total number of files
	uint16_t fileCount = 0;
	infile.read(reinterpret_cast<char*>(&fileCount), sizeof(fileCount));

	// Read total number of characters in each file, filename and directories
	std::filesystem::path p(infileName);
	if (!std::filesystem::exists(p))
		throw std::runtime_error("ERROR: Compressed file couldn't be found");
	p = p.parent_path() / p.stem().concat(" (decompressed)");

	char ch;
	int chars = 0;
	std::string fileData;
	for (int i = 0; i < fileCount; i++) {
		infile.read(reinterpret_cast<char*>(&chars), sizeof(chars));

		while (infile.get(ch)) {
			fileData += ch;
			if (ch == FILE_NAME_SEPARATOR) {
				fileData.pop_back();

				auto path = p / fileData;
				if (!std::filesystem::exists(path.parent_path())) {
					if (!std::filesystem::create_directories(path.parent_path())) {
						throw std::runtime_error("ERROR : Couldn't create output directories");
					}
				}
				files.enqueue(fileInfo(chars, path));

				fileData.clear();
				break;
			}
		}
	}
}

void Decompressor::writeIntoFile(const std::string& infileName) {
	std::ofstream outfile(files.getFront().filePath, std::ios::out | std::ios::binary | std::ios::trunc);
	if (!outfile)
		throw std::runtime_error("Output Error : \'" + files.getFront().filePath.string() + "\' couldn't be created");

	char ch;
	int fileChars = 0;
	BinNode* curr = rootNode;
	while (infile.read(reinterpret_cast<char*>(&ch), sizeof(ch)) && !files.isEmpty()) {
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

				fileChars++;
				if (fileChars == files.getFront().fileSize) {
					fileChars = 0;
					files.dequeue();

					outfile.flush();
					outfile.close();

					if (files.isEmpty()) break;

					outfile.open(files.getFront().filePath, std::ios::out | std::ios::binary | std::ios::trunc);
					if (!outfile)
						throw std::runtime_error("Output Error : \'" + files.getFront().filePath.string() + "\' couldn't be created");
				}
			}
		}
	}

	infile.close();
	outfile.flush();
	outfile.close();

	if (!fileChars && !files.isEmpty())
		throw std::runtime_error("ERROR: Compressed file is corrupted");
}

void Decompressor::decompressFile(const std::string& infileName) {
	std::cout << "Decompressing ..." << std::endl;
	auto start = std::chrono::steady_clock::now();

	infile.open(infileName, std::ios::in | std::ios::binary);
	if (!infile)
		throw std::runtime_error("Input Error : \'" + infileName + "\' couldn't be opened");

	std::cout << "Build decoding Tree ..." << std::endl;
	readHeader(infileName, infile);

	std::cout << "Decoding Characters ..." << std::endl;
	writeIntoFile(infileName);

	std::cout << "Success : Decompression Completed.\n" << std::endl;

	auto stop = std::chrono::steady_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);
	std::cout << "Decompression Time: " << duration.count() << " seconds\n" << std::endl;
	
	clear();
}
