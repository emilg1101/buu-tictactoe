#include <iostream>
#include "console/ConsoleDisplay.h"
#include "game/Game.h"
#include "game/player/FirstPlayer.h"
#include "game/player/SecondPlayer.h"
#include "game/player/ComputerPlayer.h"
#include "game/storage/Saver.h"
#include <fstream>
int main() {
    Saver *saver = new Saver();
    saver->hasSavedGame();

    Display *display = new ConsoleDisplay();
    Configuration configuration = display->getConfiguration();

    PlayerIOStream *firstPlayer = new FirstPlayer(display);
    PlayerIOStream *secondPlayer;

    if (configuration.IS_MULTIPLAYER) {
        secondPlayer = new SecondPlayer(display);
    } else {
        secondPlayer = new ComputerPlayer();
    }

    Game game = Game(firstPlayer, secondPlayer, display, saver);
    game.start();
    int i;
    cin >> i;

    return 0;
}