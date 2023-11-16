#pragma once

#include <cstdint>
#include <string>
#include <iostream>

enum Piece_Type : uint8_t {
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING,
    PIECES,
    ATTACKS,
};

enum Color : uint8_t {
    WHITE,
    BLACK
};

enum Castling_Type : uint64_t {
    CASTLE_NONE = 0ULL,
    CASTLE_WHITE_KINGSIDE = 2ULL,
    CASTLE_WHITE_QUEENSIDE = 32ULL,
    CASTLE_BLACK_KINGSIDE = 144115188075855872ULL,
    CASTLE_BLACK_QUEENSIDE = 2305843009213693952ULL
};

constexpr uint8_t BOARD_SIZE = 64;
const std::string PIECE_SYMBOLS = "PNBRQKpnbrqk";

class Board {
public:
    // Constructor
    Board();
    explicit Board(const std::string &fen);

    // Additional functions
    void print_board() const;
    void load_FEN(const std::string &fen);
    void reset_bitboards();
    void update_bitboards();

    // Bitboards
    uint64_t bitboards[2][8];
    uint64_t all_pieces;

    // Additional game state information
    uint8_t active_color;
    uint64_t castling_rights;
    uint64_t en_passant_square;
    uint8_t half_move_clock;
    uint8_t full_move_number;
};