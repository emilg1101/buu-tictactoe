#ifndef BUU_TICTACTOE_STRUCTS_H
#define BUU_TICTACTOE_STRUCTS_H

#include <vector>

using namespace std;

struct Position {
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