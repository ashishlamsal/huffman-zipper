#pragma once
#include <string>
#include <cstddef>       // For size_t
#include <cstdint>       // For uintptr_t
#include <cstring>       // For strlen

static const int HASH_SEED = 5381;               // Starting point for first cycle
static const int HASH_MULTIPLIER = 33;           // Multiplier for each cycle
static const int HASH_MASK = unsigned(-1) >> 1;  // All 1 bits except the sign

int hashCode(int key);
int hashCode(bool key);
int hashCode(char key);
int hashCode(unsigned int key);
int hashCode(long key);
int hashCode(unsigned long key);
int hashCode(short key);
int hashCode(unsigned short key);

#ifdef _WIN64
int hashCode(uintptr_t key);
#endif // _WIN64

int hashCode(void* key);
int hashCode(const char* base, size_t numBytes);
int hashCode(const char* str);
int hashCode(const std::string& str);
int hashCode(double key);
int hashCode(float key);
int hashCode(long double key);
