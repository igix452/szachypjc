#include "cli.h"
#include "pieces/bishop.h"
#include "pieces/king.h"
#include "pieces/knight.h"
#include "pieces/pawn.h"
#include "pieces/piece.h"
#include "pieces/queen.h"
#include "pieces/rook.h"
#include <iostream>

void CLI::displayPiece(Piece *piece)
{
    std::string x = "";
    if (piece) {
        if (dynamic_cast<const King*>(piece)) {
            x = (piece->getColor() == WHITE ? "K" : "k");
        } else if (dynamic_cast<const Queen*>(piece)) {
            x = (piece->getColor() == WHITE ? "Q" : "q");
        } else if (dynamic_cast<const Rook*>(piece)) {
            x = (piece->getColor() == WHITE ? "R" : "r");
        } else if (dynamic_cast<const Bishop*>(piece)) {
            x = (piece->getColor() == WHITE ? "B" : "b");
        } else if (dynamic_cast<const Knight*>(piece)) {
            x = (piece->getColor() == WHITE ? "N" : "n");
        } else if (dynamic_cast<const Pawn*>(piece)) {
            x = (piece->getColor() == WHITE ? "P" : "p");
        }
    } else {
        x = ("-"); // Czyści tekst przycisku, jeśli nie ma figury
    }
    std::cout<<x;
}

void CLI::displayBoard(ChessBoard board)
{
    std::cout<<std::endl;
    for (int i = 7; i >= 0; i--) {
        for (int j = 0; j < 8; j++) {
            displayPiece(board.getPiece(Square(j,i)));
            std::cout<<" ";
        }
        std::cout<<std::endl;
    }
}
