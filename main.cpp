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
        int a;
        cin >> a;
        if (a % 2 == 0) {
            display = new GraphicalDisplay(this);
        } else {
            display = new ConsoleDisplay(this);
        }
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
        Save save = saver->getSave();
        Field field = save.field;
        bool isMultiplayer = save.isMultiplayer;
        int lastMove = save.lastMovePlayer;
        string firstPlayerName = save.firstPlayer;
        string secondPlayerName = save.secondPlayer;

        PlayerIOStream *firstPlayer = new Player(display, CROSS_CELL_CODE);
        PlayerIOStream *secondPlayer;

        if (isMultiplayer) {
            secondPlayer = new Player(display, CIRCLE_CELL_CODE);
        } else {
            secondPlayer = new ComputerPlayer(CIRCLE_CELL_CODE);
        }

        display->setFirstPlayerName(firstPlayerName);
        display->setSecondPlayerName(secondPlayerName);

        game = new Game(firstPlayer, secondPlayer, display, saver);
        game->setField(field);
        game->setLastPlayer(lastMove);
        game->start();
    }

    void newGame() override {
        Configuration configuration = display->getConfiguration();

        PlayerIOStream *firstPlayer;
        PlayerIOStream *secondPlayer;

        if (configuration.IS_MULTIPLAYER) {
            firstPlayer = new Player(display, CROSS_CELL_CODE);
            secondPlayer = new Player(display, CIRCLE_CELL_CODE);
        } else {
            if (configuration.IS_COMPUTER_FIRST) {
                firstPlayer = new ComputerPlayer(CROSS_CELL_CODE);
                secondPlayer = new Player(display, CIRCLE_CELL_CODE);
            } else {
                firstPlayer = new Player(display, CROSS_CELL_CODE);
                secondPlayer = new ComputerPlayer(CIRCLE_CELL_CODE);
            }
        }

        saver->setFirstPlayerName(display->getFirstPlayerName());
        saver->setSecondPlayerName(display->getSecondPlayerName());
        saver->setIsMultiPlayer(configuration.IS_MULTIPLAYER);
        game = new Game(firstPlayer, secondPlayer, display, saver);
        game->setField(Field(FIELD_SIZE));
        game->setLastPlayer(CIRCLE_CELL_CODE);
        game->start();
    }

    void back() override {
        Save save = saver->getSave();
        if (save.isMultiplayer) {
            cout << "\nnot allowed in multiplayer mode\n";
        } else {
            game->moveBack();
        }
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