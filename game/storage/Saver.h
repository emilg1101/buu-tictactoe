#ifndef BUU_TICTACTOE_SAVER_H
#define BUU_TICTACTOE_SAVER_H


#include "../../Structs.h"

class Saver {
public:
    Saver();

    bool hasSavedGame();

    Save getSave();

    void newSave(Field field, int lastMovePlayer);
};

#endif //BUU_TICTACTOE_SAVER_H
