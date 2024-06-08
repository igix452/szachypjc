#ifndef MOVEMANAGER_H
#define MOVEMANAGER_H

#include "chessboard.h"
#include "gamestatus.h"
#include "move.h"
#include "pieces/piece.h"
#include <list>
class MoveManager
{
private:
    ChessBoard* board;
    GameStatus* status;
    std::list<Move> movesList;
public:
    MoveManager();
    void handleMove(const Square &from, const Square &to);
    std::vector<Square> getLegalMoves(const Square &position) const;
    bool canCastle(const PieceColor &color, const bool &kingSide) const;
    std::list<Move> getMovesList();
    Move* getLastMove();
};

#endif // MOVEMANAGER_H
