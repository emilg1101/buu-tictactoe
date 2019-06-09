#include "Game.h"

PlayerIOStream *playerFirst;
PlayerIOStream *playerSecond;

Display *display;

Field field;

Game::Game(PlayerIOStream *_playerFirst, PlayerIOStream *_playerSecond, Display *_display) {
    playerFirst = _playerFirst;
    playerSecond = _playerSecond;
    display = _display;
    field = Field(11);
}

void Game::start() {
    display->drawField(field);

    playerFirst->setField(field);
    playerSecond->setField(field);

    while (true) {
        playerFirst->getMove();
        playerSecond->getMove();
    }
}

bool checkPosition(Position position) {
    return true;
}
