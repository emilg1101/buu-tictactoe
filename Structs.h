#ifndef BUU_TICTACTOE_STRUCTS_H
#define BUU_TICTACTOE_STRUCTS_H

#include <vector>
#include <string>

using namespace std;

const int BLANK_CELL_CODE = 0;
const int CROSS_CELL_CODE = 1;
const int CIRCLE_CELL_CODE = 2;

const int FIRST_PLAYER_WIN = 0;
const int SECOND_PLAYER_WIN = 1;
const int DRAW = 2;

const string MESSAGE_POSITION_FILLED = "position is already filled, choose another one!";

struct Position {
    Position(int x, int y) : x(x), y(y) {}

    int x, y;
};

struct Configuration {

    bool IS_MULTIPLAYER;

    int FIELD_SIZE = 11;
};

class Field {
public:

    int size;

    Field() {};

    Field(int size) : dArray(size, vector<int>(size)) {
        this->size = size;
    }

    vector<int> &operator[](int i) {
        return dArray[i];
    }

    const vector<int> &operator[](int i) const {
        return dArray[i];
    }

    int getSize() const {
        return size;
    }

private:
    vector<vector<int>> dArray;
};


#endif