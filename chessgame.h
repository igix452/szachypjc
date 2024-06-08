#ifndef CHESSGAME_H
#define CHESSGAME_H

#include "chessboard.h"
#include "move.h"
#include "pieces/PieceColor.h"
#include <list>
#include "player.h"

class ChessGame
{
private:
    std::list<Move> movesList;
    PieceColor turn;
    ChessBoard board;
    int idleMovesCounter;
    bool timeControlEnabled;
    int incrementTime;
public:
    std::unique_ptr<Player> whitePlayer;
    std::unique_ptr<Player> blackPlayer;
    const Move *getLastMove() const;
    ChessBoard* getBoard();
    void initializeGame();
    PieceColor getTurn() const;
    bool isCheckmate(const PieceColor& color) const;
    bool isStalemate(const PieceColor& color) const;
    bool isPromotion() const;
    std::vector<Square> getLegalMoves(const Square& position) const;
    bool canCastle(const PieceColor &color, const bool &kingSide) const;
    bool couldCastle(const PieceColor &color, const bool &kingSide) const;
    void makeMove(const Square& startSquare, const Square& endSquare);
    void loadFEN(std::string FENPosition);
    std::string getFENPosition();
};

#endif // CHESSGAME_H
