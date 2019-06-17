#include <iostream>
#include "ComputerPlayer.h"
#include "../algorithm/WinningCheckAlgorithm.h"

struct Move {
    int row, col;
};

extern Field _field = Field(11);

extern WinningCheckAlgorithm checkAlgorithm;

ComputerPlayer::ComputerPlayer() {
    checkAlgorithm = WinningCheckAlgorithm();
}


bool checkWin(Field field, int type, Position pos) {
    return checkAlgorithm.checkWin(field, type, pos);
}

bool isMovesLeft(Field field) {
    for (int i = 0; i < field.getSize(); i++)
        for (int j = 0; j < field.getSize(); j++)
            if (field[i][j] == BLANK_CELL_CODE)
                return true;
    return false;
}

int evaluate(Field field) {
    for (int i = 0; i < field.getSize(); i++) {
        for (int j = 0; j < field.getSize(); j++) {
            if (/*field[i][j] == BLANK_CELL_CODE || */field[i][j] == CIRCLE_CELL_CODE) {
                //return checkWin(CIRCLE_CELL_CODE, Position(i, j));
                if (checkWin(field, CIRCLE_CELL_CODE, Position(i, j))) {
                    return 1;
                }
            }
        }
    }

    for (int i = 0; i < field.getSize(); i++) {
        for (int j = 0; j < field.getSize(); j++) {
            if (/*field[i][j] == BLANK_CELL_CODE || */field[i][j] == CROSS_CELL_CODE) {
                //return -1 * checkWin(CROSS_CELL_CODE, Position(i, j));
                if (checkWin(field, CROSS_CELL_CODE, Position(i, j))) {
                    return -1;
                }
            }
        }
    }

    int flag=0;
    for(int i=0;i<field.getSize();i++)
    {
        for(int j=0;j<field.getSize();j++)
        {
            if(field[i][j]==BLANK_CELL_CODE)
                flag=1;
        }
    }
    if(flag)
        return -2;
    else
        return 0;
}

int minimax(Field field, int depth, bool isMax, int alpha, int beta) {
    cout << depth << endl;
   /* if (depth == 1)
        return 0;*/
    int score = evaluate(field);
    int value;

    /*if (depth == 100)
        return score;*/

    /*if (score == 1)
        return score;

    if (score == -1)
        return score;

    if (score == 0)
        return score;*/

    if (!isMovesLeft(field))
        return score;

    if (isMax) {
        score = -99;

        bool f = false;
        for (int i = 0; i < field.getSize(); i++) {
            if (f) break;
            for (int j = 0; j < field.getSize(); j++) {
                if (field[i][j] == BLANK_CELL_CODE) {
                    field[i][j] = CIRCLE_CELL_CODE;
                    value = minimax(field, depth + 1, !isMax, alpha, beta);

                    if (value > score) {
                        score = value;
                    }

                    alpha = max(alpha, score);

                    field[i][j] = BLANK_CELL_CODE;

                    if (beta <= alpha) {
                        f = true;
                        break;
                    }
                }
            }
        }
       // return best;
    } else {
        score = 99;
        bool f = false;
        for (int i = 0; i < field.getSize(); i++) {
            if (f) break;
            for (int j = 0; j < field.getSize(); j++) {
                if (field[i][j] == BLANK_CELL_CODE) {
                    field[i][j] = CROSS_CELL_CODE;

                    value = minimax(field, depth + 1, !isMax, alpha, beta);

                    if (value < score) {
                        score = value;
                    }

                    beta = min (beta, score);

                    field[i][j] = BLANK_CELL_CODE;

                    if (beta <= alpha) {
                        f = true;
                        break;
                    }
                }
            }
        }
        //return best;
    }
    return score;
}

Move findBestMove(Field field) {
    int bestVal = -1000;
    Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;

    for (int i = 0; i < field.getSize(); i++) {
        for (int j = 0; j < field.getSize(); j++) {
            if (field[i][j] == BLANK_CELL_CODE) {
                field[i][j] = CIRCLE_CELL_CODE;

                int moveVal = minimax(field, 0, false, 99, -99);

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
    return Position(bestMove.row, bestMove.col);
}

void ComputerPlayer::setMove(Position position, int cellType) {
    _field[position.x][position.y] = cellType;
    /*for (int i = 0; i < _field.getSize(); i++) {
        for (int j = 0; j < _field.getSize(); j++) {
            cout << _field[i][j] << " ";
        }
        cout << endl;
    }*/
}