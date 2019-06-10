#ifndef BUU_TICTACTOE_GAME_H
#define BUU_TICTACTOE_GAME_H

#include "PlayerIOStream.h"
#include "Display.h"

class Game {
public:
    Game(PlayerIOStream *_playerFirst, PlayerIOStream *_playerSecond, Display *_display);

    void start();

    void fillField(Position position, int code);

    bool chickWin(Field field, int type, Position newPosition);

    bool makeMove(int playerType, PlayerIOStream *player);

    int countVertical(Field field, int type, Position position);

    int countHorizontal(Field field, int type, Position position);

    int countDiagonalLeftToRight(Field field, int type, Position position);

    int countDiagonalRightToLeft(Field field, int type, Position position);
};

#endif
