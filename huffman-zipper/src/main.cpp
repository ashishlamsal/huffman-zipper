#include "Compressor.h"
#include "Decompressor.h"
#include "HuffmanCompress.h"
#include "HuffmanDecompress.h"

#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <numeric>
#include <execution>

//void printDirSize(const std::string& dir) {
//	std::vector<std::filesystem::path> paths;
//	std::filesystem::recursive_directory_iterator dirpos(dir);
//	std::copy(begin(dirpos), end(dirpos), std::back_inserter(paths));
//
//	for (auto&& path : paths) {
//		std::cout << path << std::endl;
//	}
//
//	auto sz = std::transform_reduce(
//		std::execution::par,
//		paths.cbegin(), paths.cend(),
//		std::uintmax_t{ 0 },
//		std::plus<>(),
//		[](const std::filesystem::path& p) {
//			return is_regular_file(p) ? file_size(p) : std::uintmax_t{ 0 };
//		});
//	std::cout << "Sum of size of regular files : " << sz << "\n";
//}


int main() {
	try {
		//-----------------------Compression-------------------------//
		/*Compressor compression;
		compression.compressFile(INPUT_FILE_PATH);*/

		//-----------------------Decompression-------------------------//
		/*Decompressor decompression;
		decompression.decompressFile(COMPRESSED_FILE_PATH);*/

		Compressor compression;
		compression.compressFiles(DIRECTORY);
		Decompressor decompression;
		decompression.decompressFile(COMPRESSED_FILE_PATH);
	}
		{
			//-----------------------Compression-------------------------//
			Compressor compression;
			compression.compressFile(INPUT_FILE_PATH);
		
			//-----------------------Decompression-------------------------//
			Decompressor decompression;
			decompression.decompressFile(COMPRESSED_FILE_PATH);
		}
		std::cout << "====================================================\n";
		{
			HuffmanCompress compress;
			compress.compressFile(INPUT_FILE_PATH);

			HuffmanDecompress decompress;
			decompress.decompressFile(COMPRESSED_FILE_PATH1);
		}
	}
	catch (std::exception& err) {
		std::cerr << err.what() << '\n';
		exit(1);
	}
	
	//printDirSize("./src");
	return 0;
};