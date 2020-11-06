#pragma once
#include<iostream>
std::unordered_map<char, int> getFrequency(std::ifstream& infile);
BinNode* createHuffmanTree(std::unordered_map<char, int> frequency);
std::unordered_map<char, std::string> generateHuffmanCode(BinNode* rootNode, std::string codeString);
void compressor(std::string infileName);
void encodeIntoFile(std::string encodedString, std::string outfileName);