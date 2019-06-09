#ifndef BUU_TICTACTOE_PLAYERIOSTREAM_H
#define BUU_TICTACTOE_PLAYERIOSTREAM_H

#include "../Structs.h"

class PlayerIOStream {
public:
    PlayerIOStream() {};

    ~PlayerIOStream() {};

    virtual Position getMove() = 0;

    virtual void setField(Field field) = 0;
};

#endif