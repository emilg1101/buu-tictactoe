#include <iostream>
#include "console/ConsoleDisplay.h"
#include "game/Game.h"
#include "game/player/FirstPlayer.h"
#include "game/player/SecondPlayer.h"

int main() {
    Display* display = new ConsoleDisplay();

    PlayerIOStream* firstPlayer = new FirstPlayer(display);
    PlayerIOStream* secondPlayer = new SecondPlayer(display);

    Game game = Game(firstPlayer, secondPlayer, display);
    game.start();
    return 0;
}