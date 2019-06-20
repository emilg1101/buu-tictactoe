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

const int FIELD_SIZE = 11;
const int WIN_COUNT = 5;

struct Position {
    Position(int x, int y) : x(x), y(y) {}

    int x, y;
};

struct Configuration {

    bool IS_MULTIPLAYER;
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

    bool inRange(Position position) {
        if (position.x < 0 || position.x >= size) return false;
        return !(position.y < 0 || position.y >= size);
    }

    int get(Position position) {
        return dArray[position.x][position.y];
    }

private:
    vector<vector<int>> dArray;
};


struct Save {
    Save(const Field &field, int lastMovePlayer) : field(field), lastMovePlayer(lastMovePlayer) {}

    Field field;
    int lastMovePlayer;
};

#endif
