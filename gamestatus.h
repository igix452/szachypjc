#ifndef GAMESTATUS_H
#define GAMESTATUS_H

#include "pieces/PieceColor.h"
#include <string>

class ChessBoard; class MoveManager; class PositionManager;// forward declarations
class GameStatus
{
private:
    ChessBoard* board;
    MoveManager* moveManager;
    PositionManager* positionManager;
    int idleMovesCounter;
    bool timeControlEnabled;
    int incrementTime;
    PieceColor turn;
public:
    GameStatus();
    bool castleAllowed(const PieceColor &color, const bool &kingSide) const;
    bool isCheckmate(const PieceColor& color) const;
    bool isStalemate(const PieceColor& color) const;
    bool isPromotion() const;
    void incIdleMoves();
    void resetIdleMoves();
    PieceColor getTurn();
    void switchTurn();
    std::string getFEN();
};

#endif // GAMESTATUS_H
