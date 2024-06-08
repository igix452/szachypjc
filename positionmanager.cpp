#include "positionmanager.h"
#include "chessboard.h"
#include <algorithm>
#include <stdexcept>
#include "pieces/bishop.h"
#include "pieces/king.h"
#include "pieces/knight.h"
#include "pieces/pawn.h"
#include "pieces/queen.h"
#include "pieces/rook.h"

PositionManager::PositionManager() {}

void PositionManager::setDefaultPosition()
{
    board->clearBoard();
    for (int i = 0; i < 8; i++) {
        // generowanie bialych pionkow
        board->setPiece(Square(i, 1), std::make_shared<Pawn>(WHITE, false, board));

        // generowanie czarnych pionkow
        board->setPiece(Square(i, 6), std::make_shared<Pawn>(BLACK, false, board));
    }
    // generowanie pozostałych figur
    // Białe figury
    board->setPiece(Square(0, 0), std::make_shared<Rook>(WHITE, false, board));
    board->setPiece(Square(1, 0), std::make_shared<Knight>(WHITE, false, board));
    board->setPiece(Square(2, 0), std::make_shared<Bishop>(WHITE, false, board));
    board->setPiece(Square(3, 0), std::make_shared<Queen>(WHITE, false, board));
    board->setPiece(Square(4, 0), std::make_shared<King>(WHITE, false, board));
    board->setPiece(Square(5, 0), std::make_shared<Bishop>(WHITE, false, board));
    board->setPiece(Square(6, 0), std::make_shared<Knight>(WHITE, false, board));
    board->setPiece(Square(7, 0), std::make_shared<Rook>(WHITE, false, board));

    // Czarne figury
    board->setPiece(Square(0, 7), std::make_shared<Rook>(BLACK, false, board));
    board->setPiece(Square(1, 7), std::make_shared<Knight>(BLACK, false, board));
    board->setPiece(Square(2, 7), std::make_shared<Bishop>(BLACK, false, board));
    board->setPiece(Square(3, 7), std::make_shared<Queen>(BLACK, false, board));
    board->setPiece(Square(4, 7), std::make_shared<King>(BLACK, false, board));
    board->setPiece(Square(5, 7), std::make_shared<Bishop>(BLACK, false, board));
    board->setPiece(Square(6, 7), std::make_shared<Knight>(BLACK, false, board));
    board->setPiece(Square(7, 7), std::make_shared<Rook>(BLACK, false, board));
}

bool PositionManager::setFENPosition()
{
    // to do
    return false;
}

bool PositionManager::isKingInCheck(const PieceColor &color) const
{
    const Square kingPosition = findKing(color);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            const Piece* piece = board->getPiece(Square(i,j));
            if (piece && piece->getColor() != color) {
                std::vector<Square> enemyMoves = piece->getValidSquares(Square(i,j));
                if (std::find(enemyMoves.begin(), enemyMoves.end(), kingPosition) != enemyMoves.end()) {
                    return true;
                }
            }
        }
    }
    return false;
}

Square PositionManager::findKing(const PieceColor &color) const
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            const Piece* piece = board->getPiece(Square(i, j));
            if (piece && piece->getColor() == color && dynamic_cast<const King*>(piece)) {
                return Square(i,j);
            }
        }
    }
    throw std::runtime_error("nie znaleziono króla na planszy");
    return Square(-1,-1);
}

void PositionManager::setBoard(ChessBoard board)
{
    this->board = &board;
}
