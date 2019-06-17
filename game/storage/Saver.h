#ifndef BUU_TICTACTOE_SAVER_H
#define BUU_TICTACTOE_SAVER_H

#include "../../Structs.h"

class Saver {
private:
    bool isMultiPlayer = false;

public:
    Saver(string _firstPlayer, string _secondPlayer);

    bool hasSavedGame();

    Save getSave();

    void newSave(Field field, int lastMovePlayer);

    void deleteSave();

    void read() const;

    void write(string line, string &fileName) const;

    void setIsMultiPlayer(bool isMultiPlayer);

    void saveField(const Field &field) const;
};

#endif //BUU_TICTACTOE_SAVER_H
