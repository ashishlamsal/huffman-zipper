#include "Compressor.h"
#include "Decompressor.h"

int main() {
	try {
		//-----------------------Compression-------------------------//
		Compressor compression;
		//compression.compressFile(INPUT_FILE_PATH);
		compression.compressFolder(DIRECTORY);
				
		//-----------------------Decompression-------------------------//
		Decompressor decompression;
		//decompression.decompressFile(COMPRESSED_FILE_PATH);
		decompression.decompressFile(COMPRESSED_FILE_PATH);

	}
	catch (std::exception& err) {
		std::cerr << err.what() << '\n';
		exit(1);
	}
	return 0;
};