#ifndef MOVE_H
#define MOVE_H

#include "pieces/piece.h"
#include "square.h"

class Move {
private:
    const Square startSquare;
    const Square endSquare;
    Piece* piece;
    Piece* capturedPiece;
public:
    Move(const Square &startSquare, const Square &endSquare, Piece* piece, Piece *capturedPiece);
    Square getStartSquare() const;
    Square getEndSquare() const;
    Piece* getPiece() const;
    Piece* getCapturedPiece() const;
};

#endif // MOVE_H
