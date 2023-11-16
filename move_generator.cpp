#include "move_generator.h"
#include "lookup_tables.h"
#include "utilities.h"

Move_Generator::Move_Generator(const Board &board) : board(board) {
    // Constructor implementation
}

uint64_t Move_Generator::get_pawn_moves(const uint8_t &square) {
    uint64_t block_north = (1ULL << (square + 8)) & board.all_pieces;
    block_north |= block_north << 8;
    uint64_t block_south = (1ULL << (square - 8)) & board.all_pieces;
    block_south |= block_south >> 8;
    uint64_t blocked_squares = (block_north | block_south);
    return (pawn_moves[board.active_color][square] & ~blocked_squares) |
           (pawn_attacks[board.active_color][square] & board.bitboards[1 - board.active_color][PIECES]);
} /// idé att testa: förberäkna alla möjligheter: pawn_attacks[pawn_offset(active_color + square) + pext(all_pieces, pawn_masks[square])]
/// + (pawn_attacks[board.active_color][square] & board.bitboards[1 - board.active_color][PIECES]);?? kan vi kombinera dessa?

uint64_t Move_Generator::get_rook_moves(const uint8_t &square) {
    return sliding_attacks[rook_offsets[square] + pext(board.all_pieces, rook_masks[square])] & 
    ~board.bitboards[board.active_color][PIECES];
}

uint64_t Move_Generator::get_bishop_moves(const uint8_t &square) {
    return sliding_attacks[bishop_offsets[square] + pext(board.all_pieces, bishop_masks[square])] & 
    ~board.bitboards[board.active_color][PIECES];
}

uint64_t Move_Generator::get_queen_moves(const uint8_t &square) {
    return get_rook_moves(square) | get_bishop_moves(square);
}

uint64_t Move_Generator::get_knight_moves(const uint8_t &square) {
    return  knight_attacks[square] & 
    ~board.bitboards[board.active_color][PIECES];
}

uint64_t Move_Generator::get_king_moves(const uint8_t &square) {
    return  king_attacks[square] & 
    ~board.bitboards[board.active_color][PIECES];
}

uint64_t Move_Generator::get_castling_moves(const uint8_t &square) {
    return sliding_attacks[rook_offsets[square] + pext(board.all_pieces, rook_masks[square])] &
    CASTLING_MASK &
    board.castling_rights;
}