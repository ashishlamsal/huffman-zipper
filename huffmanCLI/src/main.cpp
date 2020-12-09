#include "Compressor.h"
#include "Decompressor.h"

int main() {
	try {
		//-----------------------Compression-------------------------//
		Compressor compression;
		compression.compressFile(R"(C:\dev\programs\huffman-test\input.txt)");
		//compression.compressFiles({ "./src/input1.txt", "./src/small-text.txt" });
		//compression.compressFolder(inputFilePath);
		Decompressor decompression;
		//decompression.decompressFile(R"(C:\dev\programs\huffman-test\huffman_1_1 (decompressed)\huffman_1 (decompressed)\huffman.huf)");

	}
	catch (std::exception& err) {
		std::cerr << err.what() << '\n';
		exit(1);
	}
	return 0;
}