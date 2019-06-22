#ifndef BUU_TICTACTOE_GRAPHICALDISPLAY_H
#define BUU_TICTACTOE_GRAPHICALDISPLAY_H

#include "../game/Display.h"
#include <SFML/Graphics.hpp>

class GraphicalDisplay : public Display {
public:
    GraphicalDisplay(CommandHandler *_handler);

    virtual ~GraphicalDisplay();

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

#endif //BUU_TICTACTOE_GRAPHICALDISPLAY_H
