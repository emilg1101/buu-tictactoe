#include "Game.h"
#include "algorithm/WinningCheckAlgorithm.h"
#include <stack>

PlayerIOStream *playerFirst;
PlayerIOStream *playerSecond;
Display *display;
Saver *saver;
stack<Position> stackMove;

Field field;

WinningCheckAlgorithm checkAlgorithm;

int lastPlayer = CIRCLE_CELL_CODE;

Game::Game(PlayerIOStream *_playerFirst, PlayerIOStream *_playerSecond, Display *_display, Saver *_saver) {
    playerFirst = _playerFirst;
    playerSecond = _playerSecond;
    display = _display;
    saver = _saver;
    checkAlgorithm = WinningCheckAlgorithm();
}

void Game::start() {
    display->drawField(field);

    bool end;
    while (true) {
        if (lastPlayer == CIRCLE_CELL_CODE) {
            end = makeMove(CROSS_CELL_CODE, playerFirst);
            if (end) {
                display->showWinner(CROSS_CELL_CODE);
                return;
            }
            lastPlayer = CROSS_CELL_CODE;
        } else {
            end = makeMove(CIRCLE_CELL_CODE, playerSecond);
            if (end) {
                display->showWinner(CIRCLE_CELL_CODE);
                return;
            }
            lastPlayer = CIRCLE_CELL_CODE;
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
    stackMove.push(position);
    fillField(position, playerType);

    display->drawField(field);
    playerSecond->setMove(position, playerType);
    saver->newSave(field, playerType);
    return checkWin(field, playerType, position);
}

void Game::moveBack() {

    if (!stackMove.empty()) {
        Position &lastMove = stackMove.top();
        playerSecond->setMove(lastMove, BLANK_CELL_CODE);
        field[lastMove.x][lastMove.y] = 0;
        stackMove.pop();

        Position &prevMove = stackMove.top();
        playerSecond->setMove(lastMove, BLANK_CELL_CODE);
        field[prevMove.x][prevMove.y] = 0;
        stackMove.pop();
        display->drawField(field);
    }
}

void Game::fillField(Position position, const int code) {
    field[position.x][position.y] = code;
}

bool Game::checkWin(Field field, int type, Position newPosition) {
    return checkAlgorithm.checkWin(field, type, newPosition);
}

void Game::setField(Field _field) {
    field = _field;
    for (int i = 0; i < field.getSize(); i++) {
        for (int j = 0; j < field.getSize(); j++) {
            if (field[i][j] != BLANK_CELL_CODE) {
                playerSecond->setMove(Position(i, j), field[i][j]);
            }
        }
    }
}

void Game::setLastPlayer(int _lastPlayer) {
    lastPlayer = _lastPlayer;
}
