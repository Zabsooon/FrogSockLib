#ifndef FSL_DATA_INTEGRITY_H_
#define FSL_DATA_INTEGRITY_H_

#include <cstdint>

// For data integrity we will make sure that we use <cstdint> lib
static_assert(sizeof(char) == 1, "Size of char is not 1 byte!");
static_assert(sizeof(signed short) == 2, "Size of signed short is not 2 bytes!");
static_assert(sizeof(signed int) == 4, "Size of signed int is not 4 bytes!");
static_assert(sizeof(signed long) == 8, "Size of signed long is not 8 bytes!");
static_assert(sizeof(signed long long) == 8, "Size of signed long long is not 8 bytes!");
static_assert(sizeof(unsigned short) == 2, "Size of unsigned short is not 2 bytes!");
static_assert(sizeof(unsigned int) == 4, "Size of unsigned int is not 4 bytes!");
static_assert(sizeof(unsigned long) == 8, "Size of unsinged long is not 8 bytes!");
static_assert(sizeof(unsigned long long) == 8, "Size of unsigned long long is not 8 bytes!");


// Just to be extra sure:
static_assert(sizeof(uint8_t) == 1, "uint8_t not 1 byte!");
static_assert(sizeof(uint16_t) == 2, "uint16_t not 2 bytes!");
static_assert(sizeof(uint32_t) == 4, "uint32_t not 4 bytes!");
static_assert(sizeof(uint64_t) == 8, "uint64_t not 8 bytes!");
static_assert(sizeof(int8_t) == 1, "int8_t not 1 byte!");
static_assert(sizeof(int16_t) == 2, "int16_t not 2 bytes!");
static_assert(sizeof(int32_t) == 4, "int32_t not 4 bytes!");
static_assert(sizeof(int64_t) == 8, "int64_t not 8 bytes!");

#endif
