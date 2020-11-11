#include<iostream>
#include<fstream>
#include<bitset>
#include<unordered_map>
#define INTERNAL_NODE_CHARACTER char(128)
#define PSEUDO_EOF char(129)
#define CHARACTER_CODE_SEPERATOR char(130)
#define HEADER_ENTRY_SEPERATOR char(131)
#define HEADER_TEXT_SEPERATOR char(132)

class Decompressor {
	std::unordered_map<char, std::string> codeMap;
public:
	std::istream infile;
private:
	void readHeader() {
		std::unordered_map<char, std::string> codeMap;
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
	std::string readAllCharFromFile() {
		char character;
		std::string encodedString;
		readHeader();
		while (infile.get(character))
		{
			std::bitset<8> bits(character);
			encodedString += bits.to_string();
		}

		return encodedString;
	}

	std::string extractTextFromFile() {
		std::string encodedString;

		encodedString = readAllCharFromFile();
		return encodedString;

	}
public:
	void decompressor(std::string infileName) {

		//infile.open("./src/" + infileName);
		std::string encodedString = extractTextFromFile();
	}
};








