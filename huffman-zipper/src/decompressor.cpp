#include<iostream>
#include<fstream>


std::string readAllCharFromFile(std::ifstream& infile) {
	char character;
	std::string encodedString;
	while (infile.get(character))
		encodedString += character;

	return encodedString;
}

std::string readEncodedFile(std::string infileName) {
	std::string encodedString;
	std::ifstream infile("./src/" + infileName);
	if (!infile) {
		std::cout << "Error: File couldn't be opened." << std::endl;
		exit(1);
	}
	encodedString = readAllCharFromFile(infile);
	infile.close();
	return encodedString;

}