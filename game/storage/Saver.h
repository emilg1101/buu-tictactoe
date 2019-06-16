#ifndef BUU_TICTACTOE_SAVER_H
#define BUU_TICTACTOE_SAVER_H

#include "../../Structs.h"

class Saver {
public:
    Saver(bool _isMultiplayer, string _firstPlayer, string _secondPlayer);

    bool hasSavedGame();

    Save getSave();

    void newSave(Field field, int lastMovePlayer);

    void deleteSave();
};

#endif //BUU_TICTACTOE_SAVER_H
