# Huffman Zipper

Data Compression and Decompression using Greedy Huffman Algorithm

![C++ Badge](https://img.shields.io/static/v1?label=C%2B%2B+&message=17&style=flat-square&logo=C%2B%2B&color=blue&labelColor=03599d)
![Visual Studio Badge](https://img.shields.io/static/v1?label=Visual+Studio&message=2019&style=flat-square&logo=visual+studio&color=grey&labelColor=5d2c92)
![Data Structures Badge](https://img.shields.io/static/v1?label=Data+Structures&message=Algorithm&style=flat-square&color=red&labelColor=007acc)
![Top Language](https://img.shields.io/github/languages/top/ashish-lamsal/huffman-zipper?style=flat-square)
![GitHub Repo Size](https://img.shields.io/github/repo-size/ashish-lamsal/huffman-zipper?style=flat-square&logo=GitHub)
![Last Commit](https://img.shields.io/github/last-commit/ashish-lamsal/huffman-zipper?style=flat-square)
![License](https://img.shields.io/github/license/ashish-lamsal/huffman-zipper?style=flat-square)

## Introduction

<p align ="justify">In computer science and information theory, a Huffman code is a particular type of optimal prefix code that is commonly used for lossless data compression. The process of finding or using such a code proceeds by means of Huffman coding, an algorithm developed by David A. Huffman while he was a Sc.D. student at MIT, and published in the 1952 paper "A Method for the Construction of Minimum-Redundancy Codes".</p>

<p align ="justify">The output from Huffman's algorithm can be viewed as a variable-length code table for encoding a source symbol (such as a character in a file). The algorithm derives this table from the estimated probability or frequency of occurrence (weight) for each possible value of the source symbol. As in other entropy encoding methods, more common symbols are generally represented using fewer bits than less common symbols. Huffman's method can be efficiently implemented, finding a code in time linear to the number of input weights if these weights are sorted. However, although optimal among methods encoding symbols separately, Huffman coding is not always optimal among all compression methods - it is replaced with arithmetic coding or asymmetric numeral systems if better compression ratio is required.

## Features

1. Compress and decompress files according to Greedy Huffman Algorithm
2. Robust program which handles any files (incuding binary files) as input
3. Best compression is obtained for text (.txt) files
4. Can compress single file or multiple files into a compressed file (.huff file)
5. Can compress a directory and its content recursively preserving file path hierarchy.
6. Extracts file, multiple files or directory from compressed file (.huff) into a folder according to compression done previously.

> This repo has three projects among which **huffman-zipper** generates *static .lib file*, **huffmanCLI** is for *command line interface* and **huffmanGUI** is for *graphical user interface*.

## How Huffman Compression Algorithm Works

The process to build a hufffman binary tree for compression is very simple and straightforward.

1. Read through the whole file and count the number of occurrence of each character

2. Create a a frequencyMap (Key/ Value pair) with character as key and its frequency as value.

3. For each symbol in frequencyMap, wrap it in a binary node. Insert them into a MinHeap Priority Queue which pops out binary node in decreasing trend of their frequency.

4. Pop the two least probable symbols from the priority queue. Combine these two symbols by adding their frequencies into a single binary node. And insert it back to the priority queue.

5. Set the two popped nodes as left and right child of the newly created node.

6. Repeat step 4 and 5 until only one tree node left in the queue which is the root node of the tree.

7. Create a CodeMap (Key/ Value pair) with character as key and its huffman code as value by assigning each symbol with its path from root node to its node, with left being 0 and right being 1.

8. Use the codeMap to compress the file.

### Compression

___

**1. How to save the tree in the compressed file?**

One of approach to write the tree in to the file is to use a pre order traversal. And later during decompression, using same traversal algorithm, we can reconstruct the tree from the file header part.

While writing tree to the compressed file, when we visit a leaf node, write bit 1 followed by the symbol in 8 bits.And when we visit an internal node (or the root node),simply write bit 0 only. So in this way, during decompression, when the program reads a bit 1, it can read the next 8 bits and wrap the char in a binary leaf node. When the program reads a bit 0, it create a new internal node and connect the two nodes as left and right child using preorder traversal algorithm.

**2. How to mark EOF of the output file?**

There are many methods to mark the EOF. For example, you can choose a character that is not present in the input file as the EOF character. However, binary files may contain character which was used pesudoEOF. So, an alternative approach would be to store file size in the file header. So the decompression program first reads the file size and, then continue to work the decompression till the required file size is reached.

**3. How to write a file header?**

The compressed file header has following structure :

| Tree    | 2 bytes   | File Size |  File Name
-------   | --------  | ------    |  -----
| Pre-order traversal of the tree | number of files to be compressed | number of chars in the each file | File name of each file

### Decompression

___

The decompression is much more easier than compression. During decompression, the program first reconstruct the tree, and then decompress the file.

## Installation

- Clone this repo to your PC
- Go to its project directory
- Open **huffman-zipper.sln** in Visual Studio 2019
- Set HuffmanCLI or HuffmanGUI as startup project 
- To build HuffamnGUI project, configure **wxWigets** for Visual Studio 2019.
- Build and run the project.

## Links

- [Wikipedia: Huffman coding](https://en.wikipedia.org/wiki/Huffman_coding)
- [Documentation]()

## How to Contribute

Pull requests are welcome. Submit Pull Request with comprehensive description of changes. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details
