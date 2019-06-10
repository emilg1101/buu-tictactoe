#include "Game.h"

PlayerIOStream *playerFirst;
PlayerIOStream *playerSecond;

const int size = 11;

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
    return chickWin(field, playerType, position);
}

void Game::fillField(Position position, const int code) {
    field[position.x][position.y] = code;
}

bool Game::chickWin(Field field, int type, Position newPosition) {
    int vert = countVertical(field, type, newPosition);
    int hor = countHorizontal(field, type, newPosition);
    int dlR = countDiagonalLeftToRight(field, type, newPosition);
    int drL = countDiagonalRightToLeft(field, type, newPosition);

    return vert > 4 || hor > 4 || dlR > 4 || drL > 4;
}

int Game::countVertical(Field field, int type, Position position) {
    int up = 0;
    int down = 0;

    for (int i = position.y + 1; i < position.y + 5; ++i) {
        if (i == size + 1 || i == -1) {
            break;
        }

        if (field[position.x][i] == type) {
            up++;
        } else {
            break;
        }
    }

    for (int i = position.y - 1; i < position.y - 5; --i) {
        if (field[position.x][i] == type) {
            down++;
        } else {
            break;
        }
    }
    return up + down;
}

int Game::countHorizontal(Field field, int type, Position position) {
    int right = 0;
    int left = 0;

    for (int i = position.x + 1; i < position.x + 5; ++i) {
        if (i == size + 1 || i == -1) {
            break;
        }

        if (field[i][position.y] == type) {
            right++;
        } else {
            break;
        }
    }

    for (int i = position.y - 1; i < position.y - 5; --i) {
        if (field[i][position.y] == type) {
            left++;
        } else {
            break;
        }
    }
    return left + right;
}

int Game::countDiagonalLeftToRight(Field field, int type, Position position) {
    int up = 0;
    int down = 0;

    for (int i = position.x + 1; i < position.x + 5; ++i) {
        for (int j = position.y + 1; j < position.y + 5; ++j) {
            if (i == size + 1 || i == -1 || j == size + 1 || j == -1) {
                break;
            }

            if (field[i][j] == type) {
                up++;
            } else {
                break;
            }
        }
    }

    for (int i = position.x - 1; i < position.x - 5; --i) {
        for (int j = position.y - 1; j < position.y - 5; --j) {
            if (i == size + 1 || i == -1 || j == size + 1 || j == -1) {
                break;
            }

            if (field[i][j] == type) {
                down++;
            } else {
                break;
            }
        }
    }

    return up + down;
}

int Game::countDiagonalRightToLeft(Field field, int type, Position position) {
    int up = 0;
    int down = 0;

    for (int i = position.x - 1; i < position.x - 5; --i) {
        for (int j = position.y + 1; j < position.y + 5; ++j) {
            if (i == size + 1 || i == -1 || j == size + 1 || j == -1) {
                break;
            }

            if (field[i][j] == type) {
                up++;
            } else {
                break;
            }
        }
    }

    for (int i = position.x + 1; i < position.x + 5; ++i) {
        for (int j = position.y - 1; j < position.y - 5; --j) {
            if (i == size + 1 || i == -1 || j == size + 1 || j == -1) {
                break;
            }

            if (field[i][j] == type) {
                down++;
            } else {
                break;
            }
        }
    }

    return up + down;
}



