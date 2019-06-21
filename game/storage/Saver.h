#ifndef BUU_TICTACTOE_SAVER_H
#define BUU_TICTACTOE_SAVER_H

#include "../../Structs.h"

class Saver {
private:
    bool isMultiPlayer = false;

    string readLineFromFile(string &fileName) const;

    void write(string line, string &fileName) const;

public:
    Saver(string _firstPlayer, string _secondPlayer);

    bool hasSavedGame();

    Save getSave();

    void newSave(Field field, int lastMovePlayer);

    void deleteSave();

    void setIsMultiPlayer(bool isMultiPlayer);

    void saveField(const Field &field) const;

    Field readField(string fileName);
};

#endif //BUU_TICTACTOE_SAVER_H
