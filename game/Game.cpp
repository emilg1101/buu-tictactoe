#include "Game.h"
#include "algorithm/WinningCheckAlgorithm.h"

PlayerIOStream *playerFirst;
PlayerIOStream *playerSecond;

const int size = 11;

Display *display;

Field field;

WinningCheckAlgorithm checkAlgorithm;

Saver *saver;

Game::Game(PlayerIOStream *_playerFirst, PlayerIOStream *_playerSecond, Display *_display, Saver *_saver) {
    playerFirst = _playerFirst;
    playerSecond = _playerSecond;
    display = _display;
    field = Field(size);
    checkAlgorithm = WinningCheckAlgorithm();
    saver = _saver;
}

void Game::start() {
    display->drawField(field);

    bool end;
    while (true) {
        end = makeMove(CROSS_CELL_CODE, playerFirst);
        if (end) {
            display->showWinner(CROSS_CELL_CODE);
            return;
        }

        end = makeMove(CIRCLE_CELL_CODE, playerSecond);
        if (end) {
            display->showWinner(CIRCLE_CELL_CODE);
            return;
        }
    }
}

Position checkPosition(Position position, PlayerIOStream *player) {
    if (field[position.x][position.y] == BLANK_CELL_CODE) {
        return position;
    } else {
        display->showWrongMove();
        return checkPosition(player->getMove(), player);
    }
}

bool Game::makeMove(int playerType, PlayerIOStream *player) {
    const Position &getMove = player->getMove();
    Position position = checkPosition(getMove, player);
    fillField(position, playerType);

    display->drawField(field);
    return checkWin(field, playerType, position);
}

void Game::fillField(Position position, const int code) {
    field[position.x][position.y] = code;
}

bool Game::checkWin(Field field, int type, Position newPosition) {
    return checkAlgorithm.checkWin(field, type, newPosition);
}
