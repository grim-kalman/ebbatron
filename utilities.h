#pragma once
#include <cstdint>

uint64_t pext(const uint64_t &bb, const uint64_t &mask);
uint64_t pdep(const uint64_t &bb, const uint64_t &mask);
uint8_t get_lsb(const uint64_t &bb);
uint8_t popcount(const uint64_t &bb);
uint8_t get_bit(const uint64_t &bb, const uint8_t &square);
void print_bitboard(const uint64_t &bb);
uint64_t string_to_position(const std::string &str);