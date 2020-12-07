/**
 * @file Constants.h
 *
 * This file exports the constants used in throughout the project.
 */

#pragma once

/// Constants for HashMap
constexpr auto INITIAL_BUCKET_COUNT = 101;
constexpr auto MAX_LOAD_PERCENTAGE = 70;

/// Constants for MinHeap
constexpr auto RESERVE_SIZE = 101;

/// Constants for Queue
const int INITIAL_QUEUE_CAPACITY = 5;

/// Constants for Huffman Tree
constexpr auto INTERNAL_NODE_CHARACTER = char(29);		// group separator	: GS

/// Constants for file Header
constexpr auto FILE_NAME_SEPARATOR = char(63);			// Question mark	: ?

// File locations
constexpr auto INPUT_FILE_PATH = "./src/huffman.huf";
constexpr auto COMPRESSED_FILE_PATH = "./src/huffman.huf";
constexpr auto DIRECTORY = "./src/huffman";
