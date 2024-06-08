#ifndef POSITIONMANAGER_H
#define POSITIONMANAGER_H


#include "pieces/PieceColor.h"
#include "square.h"
class ChessBoard; //forward declaration
class PositionManager
{
private:
    ChessBoard* board;
public:
    PositionManager();
    void setDefaultPosition();
    bool setFENPosition();
    bool isKingInCheck(const PieceColor &color) const;
    Square findKing(const PieceColor &color) const;
    void setBoard(ChessBoard board);
};

#endif // POSITIONMANAGER_H
