#ifndef BUU_TICTACTOE_PLAYERIOSTREAM_H
#define BUU_TICTACTOE_PLAYERIOSTREAM_H

#include "../Structs.h"

class PlayerIOStream {
public:
    int type;

    PlayerIOStream(int _type) {
        type = _type;
    }

    ~PlayerIOStream() {}

    virtual Position getMove() = 0;

    virtual void setMove(Position position, int cellType) = 0;
};

#endif