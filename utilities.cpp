#include <iostream>
#include <immintrin.h>
#include "utilities.h"

uint64_t pext(const uint64_t &bb, const uint64_t &mask) {
    return _pext_u64(bb, mask);
}

uint64_t pdep(const uint64_t &bb, const uint64_t &mask) {
    return _pdep_u64(bb, mask);
}

uint8_t get_lsb(const uint64_t &bb) {
    return __builtin_ctzll(bb);
}

uint8_t pop_count(const uint64_t &bb) {
    return _mm_popcnt_u64(bb);
}

uint8_t get_bit(const uint64_t &bb, const uint8_t &square) {
    return (bb >> square) & 1ULL;
}

void print_bitboard(const uint64_t &bb) {
    for (int rank = 7; rank >= 0; --rank) {
        for (int file = 7; file >= 0; --file) {
            uint64_t square_mask = 1ULL << (rank * 8 + file);
            if (bb & square_mask) {
                std::cout << "1 ";
            } else {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }
}

uint64_t string_to_position(const std::string &str) {
    char file = str[0];
    char rank = str[1];
    int file_index = file - 'a';
    int rank_index = rank - '1';
    int square = rank_index * 8 + file_index;
    return 1ULL << square;
}