#include <iostream>
#include "Game.h"

PlayerIOStream *playerFirst;
PlayerIOStream *playerSecond;

const int size = 11;
const int win = 3;

Display *display;

Field field;

Game::Game(PlayerIOStream *_playerFirst, PlayerIOStream *_playerSecond, Display *_display) {
    playerFirst = _playerFirst;
    playerSecond = _playerSecond;
    display = _display;
    field = Field(size);
}

void Game::start() {
    display->drawField(field);

    playerFirst->setField(field);
    playerSecond->setField(field);

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

//    TODO: эту прорисовку нужно изменить Назару
    display->drawField(field);
    return chickWin(field, playerType, position);
}

void Game::fillField(Position position, const int code) {
    field[position.x][position.y] = code;
}

bool Game::chickWin(Field field, int type, Position newPosition) {
    int vert = countVertical(field, type, newPosition) + 1;
    int hor = countHorizontal(field, type, newPosition) + 1;
    int dlR = countDiagonalRightToLeft(field, type, newPosition) + 1;
    int drL = countDiagonalLeftToRight(field, type, newPosition) + 1;

    return vert == win || hor == win || dlR == win || drL == win;
}

int Game::countVertical(Field field, int type, Position position) {
    int up = 0;
    int down = 0;

    for (int i = position.y + 1; i < position.y + win; i++) {
        if (i == size || i == -1) {
            break;
        }

        if (field[position.x][i] == type) {
            up++;
        } else {
            break;
        }
    }

    for (int i = position.y - 1; i > position.y - win; i--) {
        if (i == size || i == -1) {
            break;
        }

        if (field[position.x][i] == type) {
            down++;
        } else {
            break;
        }
    }

    cout << "\nup: " << up << " down: " << down << endl;
    return up + down;
}

int Game::countHorizontal(Field field, int type, Position position) {
    int right = 0;
    int left = 0;

    for (int i = position.x + 1; i < position.x + win; ++i) {
        if (i == size || i == -1) {
            break;
        }

        if (field[i][position.y] == type) {
            right++;
        } else {
            break;
        }
    }

    for (int i = position.x - 1; i > position.x - win; --i) {
        if (i == size || i == -1) {
            break;
        }

        if (field[i][position.y] == type) {
            left++;
        } else {
            break;
        }
    }
    cout << "left: " << left << " right: " << right << endl;
    return left + right;
}

int Game::countDiagonalRightToLeft(Field field, int type, Position position) {
    int upLeft = 0;
    int downRight = 0;

    for (int i = 1; i < win; i++) {
        int xDown = position.x - i;
        int yUp = position.y - i;

        if (xDown == size || xDown == -1 || yUp == size || yUp == -1) {
            break;
        }

        if (field[xDown][yUp] == type) {
            upLeft++;
        } else {
            break;
        }
    }

    for (int i = 1; i < win; i++) {
        int xUp = position.x + i;
        int yDown = position.y + i;

        if (xUp == size || xUp == -1 || yDown == size || yDown == -1) {
            break;
        }

        if (field[xUp][yDown] == type) {
            downRight++;
        } else {
            break;
        }
    }

    cout << "diagonal right to left up: " << upLeft << " down: " << downRight << endl;
    return upLeft + downRight;
}

int Game::countDiagonalLeftToRight(Field field, int type, Position position) {
    int upRight = 0;
    int downLeft = 0;

    for (int i = 1; i < win; i++) {
        int xUp = position.x + i;
        int yUp = position.y - i;

        if (xUp == size || xUp == -1 || yUp == size || yUp == -1) {
            break;
        }

        if (field[xUp][yUp] == type) {
            upRight++;
        } else {
            break;
        }
    }

    for (int i = 1; i < win; i++) {
        int xDown = position.x - i;
        int yDown = position.y + i;

        if (xDown == size || xDown == -1 || yDown == size || yDown == -1) {
            break;
        }

        if (field[xDown][yDown] == type) {
            downLeft++;
        } else {
            break;
        }
    }

    cout << "diagonal left to right up: " << upRight << " down: " << downLeft << endl;
    return downLeft + upRight;
}



