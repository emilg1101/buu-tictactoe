#ifndef BUU_TICTACTOE_FIRSTPLAYER_H
#define BUU_TICTACTOE_FIRSTPLAYER_H

#include "../PlayerIOStream.h"
#include "../Display.h"

class Player : public PlayerIOStream {
public:
    Player(Display *_display, int _type);

    Position getMove() override;

    void setMove(Position position, int cellType) override;
};

#endif //BUU_TICTACTOE_FIRSTPLAYER_H
