#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "player.h"

class HumanPlayer : public Player
{
private:
public:
    void resign(ChessGame& game);
    void requestDraw(ChessGame& game);
};

#endif // HUMANPLAYER_H
