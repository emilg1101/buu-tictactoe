#ifndef BUU_TICTACTOE_COMPUTERPLAYER_H
#define BUU_TICTACTOE_COMPUTERPLAYER_H

#include "../PlayerIOStream.h"
#include "../../Structs.h"

class ComputerPlayer : public PlayerIOStream {
public:
    ComputerPlayer(int _type);

    Position getMove() override;

    void setMove(Position position, int cellType) override;
};

#endif //BUU_TICTACTOE_COMPUTERPLAYER_H
