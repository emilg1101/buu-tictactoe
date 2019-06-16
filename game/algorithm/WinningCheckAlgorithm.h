#ifndef BUU_TICTACTOE_WINNINGCHECKALGORITHM_H
#define BUU_TICTACTOE_WINNINGCHECKALGORITHM_H

#include "../../Structs.h"

class WinningCheckAlgorithm {
public:
    WinningCheckAlgorithm();

    bool checkWin(Field field, int type, Position newPosition);
};

#endif //BUU_TICTACTOE_WINNINGCHECKALGORITHM_H
