#ifndef BUU_TICTACTOE_COMPUTERPLAYER_H
#define BUU_TICTACTOE_COMPUTERPLAYER_H

#include "../PlayerIOStream.h"
#include "../../Structs.h"

class ComputerPlayer : public PlayerIOStream {
public:
    ComputerPlayer();

    Position getMove() override;

    void setField(Field field) override;
};

#endif //BUU_TICTACTOE_COMPUTERPLAYER_H
