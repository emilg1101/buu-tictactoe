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

    bool end;
    while (true) {
        end = makeMove(CROSS_CELL_CODE, playerFirst);
        if (end) {
            return;
        }

        end = makeMove(CIRCLE_CELL_CODE, playerSecond);
        if (end) {
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
    Position position = checkPosition(player->getMove(), player);
    fillField(position, playerType);

//    TODO: эту прорисовку нужно изменить Назару
    display->drawField(field);
    return chickWin(field, playerType);
}

void Game::fillField(Position position, const int code) {
    field[position.x][position.y] = code;
}

bool Game::chickWin(Field field, int type) {
    int vert = countVertical(field, type);
    int hor = counHorizontal(field, type);
    return false;
}

int Game::countVertical(Field field, int type) {
    return 0;
}

int Game::counHorizontal(Field field, int type) {
    return 0;
}


