#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "pieces/piece.h"
#include "square.h"
#include <memory>

class ChessBoard
{
private:
    std::array<std::array<std::shared_ptr<Piece>, 8>, 8> board;
public:
    void clearBoard();
    Piece* getPiece(const Square& position) const;
    void setPiece(const Square& position, std::shared_ptr<Piece> piece);
    void movePiece(const Square& from, const Square& to);
    void promotePawn(const Square& pawnSquare, PieceType promotedPieceType);
};
#endif // CHESSBOARD_H
