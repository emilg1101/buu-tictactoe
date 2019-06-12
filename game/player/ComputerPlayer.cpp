#include <iostream>
#include "ComputerPlayer.h"

struct Move {
    int row, col;
};

extern Field field;

ComputerPlayer::ComputerPlayer() {
    field = Field(11);
}


int checkY(Position pos, int type, int dir) {
    Position newPos = Position(pos.x, pos.y+dir);
    if (!field.inRange(newPos)) return 0;
    if (field.get(newPos) != type) return 0;
    return 1 + checkY(newPos, type, dir);
}

int checkX(Position pos, int type, int dir) {
    Position newPos = Position(pos.x+dir, pos.y);
    if (!field.inRange(newPos)) return 0;
    if (field.get(newPos) != type) return 0;
    return 1 + checkX(newPos, type, dir);
}

int checkXY(Position pos, int type, int xdir, int ydir) {
    Position newPos = Position(pos.x + xdir, pos.y + ydir);
    if (!field.inRange(newPos)) return 0;
    if (field.get(newPos) != type) return 0;
    return 1 + checkXY(newPos, type, xdir, ydir);
}

bool checkWin(int type, Position pos) {

    int vert = checkY(pos, type, -1) + checkY(pos, type, 1) + 1;
    int hor = checkX(pos, type, -1) + checkX(pos, type, 1) + 1;
    int lr = checkXY(pos, type, 1, 1) + checkXY(pos, type, -1, -1) + 1;
    int rl = checkXY(pos, type, -1, 1) + checkXY(pos, type, 1, -1) + 1;

    //cout << "checkWin" << endl;
    return vert == WIN_COUNT || hor == WIN_COUNT || lr == WIN_COUNT || rl == WIN_COUNT;
}

bool isMovesLeft() {
    for (int i = 0; i < field.getSize(); i++)
        for (int j = 0; j < field.getSize(); j++)
            if (field[i][j] == BLANK_CELL_CODE)
                return true;
    return false;
}

int evaluate() {
    for (int i = 0; i < field.getSize(); i++) {
        for (int j = 0; j < field.getSize(); j++) {
            if (checkWin(CIRCLE_CELL_CODE, Position(i, j))) {
                return  10;
            }
        }
    }

    for (int i = 0; i < field.getSize(); i++) {
        for (int j = 0; j < field.getSize(); j++) {
            if (checkWin(CROSS_CELL_CODE, Position(i, j))) {
                return  -10;
            }
        }
    }

    return 0;
}

int minimax(int depth, bool isMax) {
    cout << depth << endl;
    if (depth == 1)
        return 0;
    int score = evaluate();

    if (score == 10)
        return score;

    if (score == -10)
        return score;

    if (isMovesLeft() == false)
        return 0;

    if (isMax) {
        int best = -1000;

        for (int i = 0; i < field.getSize(); i++) {
            for (int j = 0; j < field.getSize(); j++) {
                if (field[i][j] == BLANK_CELL_CODE) {
                    field[i][j] = CIRCLE_CELL_CODE;
                    best = max(best, minimax(depth + 1, !isMax));

                    field[i][j] = BLANK_CELL_CODE;
                }
            }
        }
        return best;
    } else {
        int best = 1000;

        for (int i = 0; i < field.getSize(); i++) {
            for (int j = 0; j < field.getSize(); j++) {
                if (field[i][j] == BLANK_CELL_CODE) {
                    field[i][j] = CROSS_CELL_CODE;

                    best = min(best, minimax(depth + 1, !isMax));

                    field[i][j] = BLANK_CELL_CODE;
                }
            }
        }
        return best;
    }
}

Move findBestMove() {
    int bestVal = -1000;
    Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;

    for (int i = 0; i < field.getSize(); i++) {
        for (int j = 0; j < field.getSize(); j++) {
            if (field[i][j] == BLANK_CELL_CODE) {
                field[i][j] = CIRCLE_CELL_CODE;

                int moveVal = minimax(0, false);

                field[i][j] = BLANK_CELL_CODE;

                if (moveVal > bestVal) {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }

    return bestMove;
}

Position ComputerPlayer::getMove() {
    Move bestMove = findBestMove();
    return Position(bestMove.row, bestMove.col);
}

void ComputerPlayer::setMove(Position position, int cellType) {
    field[position.x][position.y] = cellType;
}