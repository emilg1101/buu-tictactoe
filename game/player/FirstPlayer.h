#ifndef BUU_TICTACTOE_FIRSTPLAYER_H
#define BUU_TICTACTOE_FIRSTPLAYER_H

#include "../PlayerIOStream.h"
#include "../Display.h"

class FirstPlayer : public PlayerIOStream {
public:
    FirstPlayer(Display *_display);

    Position getMove() override;

    void setMove(Position position, int cellType) override;
};

#endif //BUU_TICTACTOE_FIRSTPLAYER_H
