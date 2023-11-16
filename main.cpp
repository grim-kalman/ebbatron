#include <iostream>
#include "Board.h"
#include "Move_Generator.h"
#include "utilities.h"

int main() {
    // Initialize Board from FEN string
    std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    Board board(fen);
    Move_Generator gen(board);

    // Generate pawn moves for each square and print them
    for (int i = 0; i < 64; i++) {
        uint64_t moves = gen.get_pawn_moves(i);
        std::cout << "Pawn moves for square " << i << ":" << std::endl;
        print_bitboard(moves);
        std::cout << std::endl;
    }

    return 0;
}