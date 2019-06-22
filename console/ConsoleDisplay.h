#ifndef BUU_TICTACTOE_CONSOLEDISPLAY_H
#define BUU_TICTACTOE_CONSOLEDISPLAY_H

#include "../game/Display.h"

class ConsoleDisplay : public Display {
public:
    ConsoleDisplay(CommandHandler *_handler);

    virtual ~ConsoleDisplay();

    Configuration getConfiguration() override;

    void drawField(Field field) override;

    Position getFirstPlayerMove() override;

    Position getSecondPlayerMove() override;

    void showWrongMove() override;

    void showWinner(int type) override;

    bool loadSavedGame() override;

    void setFirstPlayerName(string name) override;

    void setSecondPlayerName(string name) override;
};

#endif
