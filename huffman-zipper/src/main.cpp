#include "Compressor.h"
#include "Decompressor.h"

#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <numeric>
#include <execution>

void printDirSize(const std::string& dir) {
	std::vector<std::filesystem::path> paths;
	std::filesystem::recursive_directory_iterator dirpos(dir);
	std::copy(begin(dirpos), end(dirpos), std::back_inserter(paths));

	for (auto&& path : paths) {
		std::cout << path << std::endl;
	}

	auto sz = std::transform_reduce(
		std::execution::par,
		paths.cbegin(), paths.cend(),
		std::uintmax_t{ 0 },
		std::plus<>(),
		[](const std::filesystem::path& p) {
			return is_regular_file(p) ? file_size(p) : std::uintmax_t{ 0 };
		});
	std::cout << "Sum of size of regular files : " << sz << "\n";
}


int main() {
	try {
		//-----------------------Compression-------------------------//
		Compressor compression;
		compression.compressFile(INPUT_FILE_PATH);

		//-----------------------Decompression-------------------------//
		Decompressor decompression;
		decompression.decompressFile(COMPRESSED_FILE_PATH);
	}
	catch (std::exception& err) {
		std::cerr << err.what() << '\n';
		exit(1);
	}

	//std::ifstream infile("./src/1.jpg", std::ios::in | std::ios::binary);
	//if (!infile) {
	//	std::cout << "File could not be opened.";
	//}
	//std::ofstream outfile("./src/2.jpg", std::ios::out | std::ios::binary);
	//if (!outfile) {
	//	std::cout << "File could not be opened.";
	//}

	//char ch;
	//while (infile.read(&ch,1))
	//{
	//	outfile.write(&ch, 1);
	//}
	//infile.close();
	//outfile.close();
	//printDirSize("./src");


	return 0;
};