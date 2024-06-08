#ifndef CLI_H
#define CLI_H
#include "chessboard.h"
#include "pieces/piece.h"
// nieużywane
class CLI
{
public:
    static void displayPiece(Piece* piece);
    static void displayBoard(ChessBoard board);
};

#endif // CLI_H
