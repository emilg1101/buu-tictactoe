#include "Game.h"

PlayerIOStream *playerFirst;
PlayerIOStream *playerSecond;

Display *display;

Game::Game(PlayerIOStream *_playerFirst, PlayerIOStream *_playerSecond, Display *_display) {
    playerFirst = _playerFirst;
    playerSecond = _playerSecond;
    display = _display;
}

void Game::start() {
    Field field = Field(20);
    display->drawField(field);

    playerFirst->setField(field);
    playerSecond->setField(field);

    while (true) {
        playerFirst->getMove();
        playerSecond->getMove();
    }
}
