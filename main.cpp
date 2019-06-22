#include <iostream>
#include "console/ConsoleDisplay.h"
#include "game/Game.h"
#include "game/player/Player.h"
#include "game/player/ComputerPlayer.h"
#include "game/storage/Saver.h"
#include "game/CommandHandler.h"
#include "gui/GraphicalDisplay.h"

class GameController : public CommandHandler {
public:
    Display *display;
    Game *game;
    Saver *saver;

    GameController() {
        display = new GraphicalDisplay(this);
        saver = new Saver();
    }

    void init() {
        if (saver->hasSavedGame() && display->loadSavedGame()) {
            loadGame();
        } else {
            newGame();
        }
    }

    void loadGame() {

        Field field = Field(11);
        field[0][0] = CROSS_CELL_CODE;
        field[1][1] = CIRCLE_CELL_CODE;
        bool isMultiplayer = false;

        PlayerIOStream *firstPlayer = new Player(display, CROSS_CELL_CODE);
        PlayerIOStream *secondPlayer;

        if (isMultiplayer) {
            secondPlayer = new Player(display, CIRCLE_CELL_CODE);
        } else {
            secondPlayer = new ComputerPlayer(CIRCLE_CELL_CODE);
        }

        display->setFirstPlayerName("player1");
        display->setSecondPlayerName("player2");

        game = new Game(firstPlayer, secondPlayer, display, saver);
        game->setField(field);
        game->setLastPlayer(CIRCLE_CELL_CODE);
        game->start();
    }

    void newGame() override {
        Configuration configuration = display->getConfiguration();

        PlayerIOStream *firstPlayer = new Player(display, CROSS_CELL_CODE);
        PlayerIOStream *secondPlayer;

        if (configuration.IS_MULTIPLAYER) {
            secondPlayer = new Player(display, CIRCLE_CELL_CODE);
        } else {
            secondPlayer = new ComputerPlayer(CIRCLE_CELL_CODE);
        }

        game = new Game(firstPlayer, secondPlayer, display, saver);
        game->start();
    }

    void exit() override {
        cout << "exit()" << endl;
    }
};

int main() {
    auto *controller = new GameController();
    controller->init();
    int i;
    cin >> i;
    return 0;
}