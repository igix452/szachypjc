#include "chessboard.h"
#include "pieces/bishop.h"
#include "pieces/knight.h"
#include "pieces/queen.h"
#include "pieces/rook.h"
#include <stdexcept>

//ChessBoard::ChessBoard() {}

void ChessBoard::clearBoard()
{ // usunięcie wszystkich figur z szachownicy
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = nullptr;
        }
    }
}

Piece *ChessBoard::getPiece(const Square &position) const
{
    if (position.isValid()) { // Sprawdza, czy pozycja jest prawidłowa
        return board[position.getFile()][position.getRank()].get(); // Zwraca wskaźnik do figury
    }
    return nullptr; // Zwraca nullptr, jeśli pozycja jest nieprawidłowa
}

void ChessBoard::setPiece(const Square &position, std::shared_ptr<Piece> piece)
{
    if (position.isValid()) {
        board[position.getFile()][position.getRank()] = std::move(piece);
    }
}

void ChessBoard::movePiece(const Square &from, const Square &to)
{
    if (from.isValid() && to.isValid()) {
        board[to.getFile()][to.getRank()] = std::move(board[from.getFile()][from.getRank()]);
    }
}

void ChessBoard::promotePawn(const Square &pawnSquare, PieceType promotedPieceType)
{ // promocja piona
    if (getPiece(pawnSquare) && getPiece(pawnSquare)->getType() == PAWN) {
        const PieceColor color = getPiece(pawnSquare)->getColor();
        if ((pawnSquare.getRank() == 7 && color == WHITE) || (pawnSquare.getRank() == 0 && color == BLACK)) {
            switch (promotedPieceType) {
            case KNIGHT:
                setPiece(pawnSquare,std::make_shared<Knight>(color, true, this));
                break;
            case BISHOP:
                setPiece(pawnSquare,std::make_shared<Bishop>(color, true, this));
                break;
            case ROOK:
                setPiece(pawnSquare,std::make_shared<Rook>(color, true, this));
                break;
            case QUEEN:
                setPiece(pawnSquare,std::make_shared<Queen>(color, true, this));
                break;
            default:
                throw std::invalid_argument("niepoprawny typ promocji");
            }
            return;
        }
        throw std::invalid_argument("blad przy promowaniu");
    }
}
