#pragma once

#include "board.h"

constexpr uint64_t CASTLING_MASK = 3891110078048108598ULL;

class Move_Generator {
public:
    // Constructor
    Move_Generator(const Board &board);

    // Additional functions
    uint64_t get_pawn_moves(const uint8_t &square);
    uint64_t get_rook_moves(const uint8_t &square);
    uint64_t get_bishop_moves(const uint8_t &square);
    uint64_t get_queen_moves(const uint8_t &square);
    uint64_t get_knight_moves(const uint8_t &square);
    uint64_t get_king_moves(const uint8_t &square);
    uint64_t get_castling_moves(const uint8_t &square);
    // Add other move generation functions here

    const Board &board;
};