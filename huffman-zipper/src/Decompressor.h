#pragma once
#include<iostream>

std::string readAllCharFromFile(std::ifstream& infile );
std::string extractTextFromFile(std::string infileName);
void decompressor(std::string);
