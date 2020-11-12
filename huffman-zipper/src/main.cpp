#include "Compressor.h"
#include "Decompressor.h"


int main() {

	//compressor 
	/*{
		Compressor compression;
		compression.compressor(INPUT_FILE_PATH);
	}*/

	//-----------------------Decompression-------------------------//
	Decompressor decompression;

	decompression.decompressor(COMPRESSED_FILE_PATH);

	return 0;
};