#include <iostream>
#include "console/ConsoleDisplay.h"
#include "game/Game.h"
#include "game/player/FirstPlayer.h"
#include "game/player/SecondPlayer.h"
#include "game/player/ComputerPlayer.h"
#include "game/storage/Saver.h"

int main() {
    Saver saver = Saver();
    Display* display = new ConsoleDisplay();

    if (saver.hasSavedGame()) {
        cout << "Has game" << endl;
    } else {
        cout << "No game" << endl;
    }

    Configuration configuration = display->getConfiguration();

    PlayerIOStream* firstPlayer = new FirstPlayer(display);
    PlayerIOStream* secondPlayer;

    if (configuration.IS_MULTIPLAYER) {
        secondPlayer = new SecondPlayer(display);
    } else {
        secondPlayer = new ComputerPlayer();
    }

    Game game = Game(firstPlayer, secondPlayer, display);
    game.start();
    return 0;
}