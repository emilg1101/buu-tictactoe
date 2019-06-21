#ifndef BUU_TICTACTOE_SAVER_H
#define BUU_TICTACTOE_SAVER_H

#include "../../Structs.h"

class Saver {
public:
    Saver() {};

    bool hasSavedGame();

    Save getSave();

    void newSave(Field field, int lastMovePlayer);

    void deleteSave();

    void setFirstPlayerName(string name);

    void setSecondPlayerName(string name);

    void setIsMultiPlayer(bool isMultiPlayer);

private:
    bool isMultiPlayer = false;

    string readLineFromFile(string &fileName) const;

    void write(string line, string &fileName) const;

    Field readField(string fileName);

    void saveField(const Field &field) const;
};

#endif //BUU_TICTACTOE_SAVER_H
