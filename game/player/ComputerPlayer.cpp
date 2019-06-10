#include "ComputerPlayer.h"

struct Move {
    int row, col;
};

extern Field field;

ComputerPlayer::ComputerPlayer() {
    field = Field(11);
}

bool isMovesLeft() {
    for (int i = 0; i < field.getSize(); i++)
        for (int j = 0; j < field.getSize(); j++)
            if (field[i][j] == BLANK_CELL_CODE)
                return true;
    return false;
}

int evaluate() {
    return 10;
}

int minimax(int depth, bool isMax) {
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