#pragma once

// Constants for HashMap
constexpr auto INITIAL_BUCKET_COUNT = 101;
constexpr auto MAX_LOAD_PERCENTAGE = 70;

// Constants for MinHeap
constexpr auto RESERVE_SIZE = 101;

// Constants for Huffman Tree
constexpr auto INTERNAL_NODE_CHARACTER = char(128);
constexpr auto PSEUDO_EOF = char(129);

// Constants for file Header
constexpr auto CHARACTER_CODE_SEPERATOR = char(130);
constexpr auto HEADER_ENTRY_SEPERATOR = char(131);
constexpr auto HEADER_TEXT_SEPERATOR = char(132);

// File locations
constexpr auto INPUT_FILE_PATH = "./src/test.txt";
constexpr auto COMPRESSED_FILE_PATH = "./src/old_comp.txt";
constexpr auto DECOMPRESSED_FILE_PATH = "./src/old_decomp.txt";

constexpr auto COMPRESSED_FILE_PATH1 = "./src/new_comp.txt";
constexpr auto DECOMPRESSED_FILE_PATH1 = "./src/new_decomp.txt";