#include <iostream>
#include <exception>

#include "Compressor.h"
#include "Decompressor.h"


int main() {
	try {
		//-----------------------Compression-------------------------//
		Compressor compression;
		compression.compressor(INPUT_FILE_PATH);

		std::cout << "======================================================================================" << std::endl;
		//-----------------------Decompression-------------------------//
		Decompressor decompression;
		decompression.decompressor(COMPRESSED_FILE_PATH);
	}
	catch (std::exception& err) {
		std::cerr << err.what() << std::endl;
	}
	return 0;
};