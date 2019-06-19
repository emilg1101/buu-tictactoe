#ifndef BUU_TICTACTOE_SECONDPLAYER_H
#define BUU_TICTACTOE_SECONDPLAYER_H

#include "../PlayerIOStream.h"
#include "../Display.h"

class SecondPlayer : public PlayerIOStream {
public:
    SecondPlayer(Display *_display);

    Position getMove() override;

    void setMove(Position position, int cellType) override;
};

#endif //BUU_TICTACTOE_SECONDPLAYER_H
