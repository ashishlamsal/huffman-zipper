#include "Compressor.h"
#include "Decompressor.h"

int main() {
	try {
		//-----------------------Compression-------------------------//
		Compressor compression;
		compression.compressFile("D:\\ProjectC++\\huffman-zipper\\huffmanGUI\\src\\huffman\\test.txt");
		//compression.compressFolder(DIRECTORY);
		//compression.compressFiles({ "./src/input1.txt", "./src/small-text.txt" });

		//-----------------------Decompression-------------------------//
		Decompressor decompression;
		decompression.decompressFile("./src/huffman.huf");
		//decompression.decompressFile(COMPRESSED_FILE_PATH);
	}
	catch (std::exception& err) {
		std::cerr << err.what() << '\n';
		exit(1);
	}
	return 0;
};