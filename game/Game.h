#ifndef BUU_TICTACTOE_GAME_H
#define BUU_TICTACTOE_GAME_H

#include "PlayerIOStream.h"
#include "Display.h"
#include "storage/Saver.h"

class Game {
public:
    Game(PlayerIOStream *_playerFirst, PlayerIOStream *_playerSecond, Display *_display, Saver *_saver);

    void start();

    void fillField(Position position, int code);

    bool checkWin(Field field, int type, Position newPosition);

    bool makeMove(int playerType, PlayerIOStream *player);
};

#endif
