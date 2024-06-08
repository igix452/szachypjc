#ifndef PLAYER_H
#define PLAYER_H

#include "move.h"
#include "pieces/PieceColor.h"
class GameStatus; //forward declaration
class Player
{
protected:
    PieceColor color;
    double timeLeft;
public:
    Player(PieceColor color, double timeLeft)
        : color(color), timeLeft(timeLeft) {}
    virtual void connectToEngine() = 0;
    virtual Move getNextMove(GameStatus* status) = 0;
    virtual void setDifficulty(int diff) = 0;
};

#endif // PLAYER_H
