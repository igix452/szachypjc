#include "move.h"

Move::Move(const Square &startSquare, const Square &endSquare, Piece* piece, Piece* capturedPiece) : startSquare(startSquare),
    endSquare(endSquare),
    piece(piece),
    capturedPiece(capturedPiece)
{}

Square Move::getStartSquare() const
{
    return startSquare;
}

Square Move::getEndSquare() const
{
    return endSquare;
}

Piece *Move::getPiece() const
{
    return piece;
}

Piece *Move::getCapturedPiece() const
{

}
