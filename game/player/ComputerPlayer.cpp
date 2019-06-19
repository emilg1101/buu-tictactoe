#include <iostream>
#include "ComputerPlayer.h"
#include "../algorithm/WinningCheckAlgorithm.h"

struct Move {
    int row, col;
};

extern Field _field = Field(11);

extern WinningCheckAlgorithm checkAlgorithm;

int moves = 0;
Position lastMove = Position(-1, -1);

ComputerPlayer::ComputerPlayer() {
    checkAlgorithm = WinningCheckAlgorithm();
}

int start(int i) {
    if (i == 0) return 0;
    if (i == _field.getSize() - 1) return i - 2;
    return i - 1;
}

int end(int i) {
    if (i == 0) return 2;
    if (i == _field.getSize() - 1) return i;
    return i + 1;
}

bool checkWin(Field field, int type, Position pos) {
    return checkAlgorithm.checkWin(field, type, pos);
}

bool isMovesLeft(Field field) {
    return moves < _field.getSize() * _field.getSize();
}

int evaluate(Field field) {
    for (int i = 0; i < field.getSize(); i++) {
        for (int j = 0; j < field.getSize(); j++) {
            if (field[i][j] == CIRCLE_CELL_CODE && checkWin(field, CIRCLE_CELL_CODE, Position(i, j))) {
                return 10;
            }
        }
    }

    for (int i = 0; i < field.getSize(); i++) {
        for (int j = 0; j < field.getSize(); j++) {
            if (field[i][j] == CROSS_CELL_CODE && checkWin(field, CROSS_CELL_CODE, Position(i, j))) {
                return -10;
            }
        }
    }
    return 0;
}

int minimax(Field field, int depth, bool isMax, int alpha, int beta) {
    int score = evaluate(field);
    if (depth == 7)
        return 0;

    if (score == 10) {
        return score - depth;
    }

    if (score == -10) {
        return score + depth;
    }

    if (!isMovesLeft(field)) {
        return 0;
    }

    if (isMax) {
        int bestVal = -999;
        for (int i = start(lastMove.x); i <= end(lastMove.x); i++) {
            for (int j = start(lastMove.y); j <= end(lastMove.y); j++) {
                if (field[i][j] == BLANK_CELL_CODE) {
                    field[i][j] = CIRCLE_CELL_CODE;
                    int val = minimax(field, depth + 1, !isMax, alpha, beta);
                    bestVal = max(bestVal, val);
                    alpha = max(bestVal, alpha);
                    field[i][j] = BLANK_CELL_CODE;
                    if (beta <= alpha)
                        break;
                }
                if (beta <= alpha)
                    break;
            }
        }
        return bestVal;
    } else {
        int bestVal = 999;
        for (int i = start(lastMove.x); i <= end(lastMove.x); i++) {
            for (int j = start(lastMove.y); j <= end(lastMove.y); j++) {
                if (field[i][j] == BLANK_CELL_CODE) {
                    field[i][j] = CROSS_CELL_CODE;
                    int val = minimax(field, depth + 1, !isMax, alpha, beta);
                    bestVal = min(bestVal, val);
                    beta = min(bestVal, beta);
                    field[i][j] = BLANK_CELL_CODE;
                    if (beta <= alpha)
                        break;
                }
                if (beta <= alpha)
                    break;
            }
        }
        return bestVal;
    }
}

Move findBestMove(Field field) {
    int bestVal = -1000;
    Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;
    int alpha = -1000;
    int beta = 1000;

    for (int i = start(lastMove.x); i <= end(lastMove.x); i++) {
        for (int j = start(lastMove.y); j <= end(lastMove.y); j++) {
            if (field[i][j] == BLANK_CELL_CODE) {
                field[i][j] = CIRCLE_CELL_CODE;

                int moveVal = minimax(field, 0, false, alpha, beta);

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
    Move bestMove = findBestMove(_field);
    _field[bestMove.row][bestMove.col] = CIRCLE_CELL_CODE;
    moves++;
    Position position = Position(bestMove.row, bestMove.col);
    lastMove = position;
    return position;
}

void ComputerPlayer::setMove(Position position, int cellType) {
    _field[position.x][position.y] = cellType;
    lastMove = position;
    moves++;
}