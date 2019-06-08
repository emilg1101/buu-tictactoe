#ifndef BUU_TICTACTOE_DISPLAY_H
#define BUU_TICTACTOE_DISPLAY_H

#include <string>
#include "PlayerIOStream.h"

using namespace std;

class Display {
public:
    Display() {}

    ~Display() {}

    virtual Configuration getConfiguration() = 0;

    virtual void drawField(Field field) = 0;

    virtual Position getFirstPlayerMove() = 0;

    virtual Position getSecondPlayerMove() = 0;

    virtual void showWrongMove() = 0;

    virtual void showWinner(int type) = 0;
};

#endif
