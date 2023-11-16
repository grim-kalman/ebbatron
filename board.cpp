#include <cstdint>
#include <sstream>
#include <iostream>
#include "board.h"
#include "utilities.h"

Board::Board() {
    // Initialize the bitboards to the starting position
    bitboards[WHITE][PAWN] =       0b0000000000000000000000000000000000000000000000001111111100000000;
    bitboards[WHITE][KNIGHT] =     0b0000000000000000000000000000000000000000000000000000000001000010;
    bitboards[WHITE][BISHOP] =     0b0000000000000000000000000000000000000000000000000000000000100100;
    bitboards[WHITE][ROOK] =       0b0000000000000000000000000000000000000000000000000000000010000001;
    bitboards[WHITE][QUEEN] =      0b0000000000000000000000000000000000000000000000000000000000010000;
    bitboards[WHITE][KING] =       0b0000000000000000000000000000000000000000000000000000000000001000;
    bitboards[WHITE][PIECES] =     0b0000000000000000000000000000000000000000000000001111111111111111;

    bitboards[BLACK][PAWN] =        0b0000000011111111000000000000000000000000000000000000000000000000;
    bitboards[BLACK][KNIGHT] =      0b0100001000000000000000000000000000000000000000000000000000000000;
    bitboards[BLACK][BISHOP] =      0b0010010000000000000000000000000000000000000000000000000000000000;
    bitboards[BLACK][ROOK] =        0b1000000100000000000000000000000000000000000000000000000000000000;
    bitboards[BLACK][QUEEN] =       0b0001000000000000000000000000000000000000000000000000000000000000;
    bitboards[BLACK][KING] =        0b0000100000000000000000000000000000000000000000000000000000000000;
    bitboards[BLACK][PIECES] =      0b1111111111111111000000000000000000000000000000000000000000000000;

    all_pieces =                    0b1111111111111111000000000000000000000000000000001111111111111111;

    // Initialize the game state variables
    active_color =      0;      // White to move first
    castling_rights = CASTLE_WHITE_KINGSIDE | CASTLE_WHITE_QUEENSIDE | CASTLE_BLACK_KINGSIDE | CASTLE_BLACK_QUEENSIDE;
    en_passant_square = 0;     // 0 for "no en passant"
    half_move_clock =   0;      // No half-moves made yet (used for the fifty-move rule)
    full_move_number =  1;      // No full-moves made yet
}

Board::Board(const std::string &fen) {
    load_FEN(fen);
}

void Board::print_board() const {
    for (size_t square = 0; square < BOARD_SIZE; square++) {
        bool found_piece = false;

        for (Color color : {WHITE, BLACK}) {
            for (Piece_Type piece_type : {PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING}) {
                uint64_t mask = 1ULL << (63 - square);
                if (bitboards[color][piece_type] & mask) {
                    std::cout << PIECE_SYMBOLS[color * 6 + piece_type] << ' ';
                    found_piece = true;
                    break;
                }
            }
            if (found_piece) break;
        }

        if (!found_piece) {
            std::cout << ". ";
        }

        if ((square & 7) == 7) {
            std::cout << std::endl;
        }
    }
}

void Board::load_FEN(const std::string &fen) {
    size_t square = 63;
    std::stringstream fen_stream(fen);
    std::string token;

    for (int i = 0; i < 6 && fen_stream >> token; i++) {
        switch (i) {
            case 0: // Piece placement
                reset_bitboards();

                for (char c : token) {
                    if (std::isdigit(c)) {
                        square -= (c - '0');
                    } else if (c == '/') {
                        continue;
                    } else {
                        Color color = islower(c) ? BLACK : WHITE;
                        Piece_Type piece_type = static_cast<Piece_Type>(PIECE_SYMBOLS.find(c) % 6);
                        bitboards[color][piece_type] |= 1ULL << square--;
                    }
                }
                update_bitboards();
                break;
            case 1: // Active color
                active_color = (token == "w" ? WHITE : BLACK);
                break;
            case 2: // Castling rights
                castling_rights = CASTLE_NONE;
                for (char c : token) {
                    switch (c) {
                        case 'K':
                            castling_rights |= CASTLE_WHITE_KINGSIDE;
                            break;
                        case 'Q':
                            castling_rights |= CASTLE_WHITE_QUEENSIDE;
                            break;
                        case 'k':
                            castling_rights |= CASTLE_BLACK_KINGSIDE;
                            break;
                        case 'q':
                            castling_rights |= CASTLE_BLACK_QUEENSIDE;
                            break;
                    }
                }
                break;
            case 3: // En passant target square
                if (token == "-") {
                    en_passant_square = 0;
                } else {
                    en_passant_square = string_to_position(token);
                }
                break;
            case 4: // Half-move clock
                half_move_clock = std::stoi(token);
                break;
            case 5: // Full move number
                full_move_number = std::stoi(token);
                break;
        }
    }
}

void Board::reset_bitboards() {
    for (auto &bb : bitboards) {
        std::fill(std::begin(bb), std::end(bb), 0);
    }
}

void Board::update_bitboards() {
        for (Piece_Type piece_type : {PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING}) {
            bitboards[WHITE][PIECES] |= bitboards[WHITE][piece_type];
            bitboards[BLACK][PIECES] |= bitboards[BLACK][piece_type];
        }
        all_pieces = bitboards[WHITE][PIECES] | bitboards[BLACK][PIECES];
}