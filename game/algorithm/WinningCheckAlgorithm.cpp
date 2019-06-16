#include "WinningCheckAlgorithm.h"

WinningCheckAlgorithm::WinningCheckAlgorithm() {}

int checkY(Field field, Position pos, int type, int dir) {
    Position newPos = Position(pos.x, pos.y + dir);
    if (!field.inRange(newPos)) return 0;
    if (field.get(newPos) != type) return 0;
    return 1 + checkY(field, newPos, type, dir);
}

int checkX(Field field, Position pos, int type, int dir) {
    Position newPos = Position(pos.x + dir, pos.y);
    if (!field.inRange(newPos)) return 0;
    if (field.get(newPos) != type) return 0;
    return 1 + checkX(field, newPos, type, dir);
}

int checkXY(Field field, Position pos, int type, int xdir, int ydir) {
    Position newPos = Position(pos.x + xdir, pos.y + ydir);
    if (!field.inRange(newPos)) return 0;
    if (field.get(newPos) != type) return 0;
    return 1 + checkXY(field, newPos, type, xdir, ydir);
}

bool WinningCheckAlgorithm::checkWin(Field field, int type, Position newPosition) {
    int vert = checkY(field, newPosition, type, -1) + checkY(field, newPosition, type, 1) + 1;
    int hor = checkX(field, newPosition, type, -1) + checkX(field, newPosition, type, 1) + 1;
    int lr = checkXY(field, newPosition, type, 1, 1) + checkXY(field, newPosition, type, -1, -1) + 1;
    int rl = checkXY(field, newPosition, type, -1, 1) + checkXY(field, newPosition, type, 1, -1) + 1;

    return vert >= WIN_COUNT || hor >= WIN_COUNT || lr >= WIN_COUNT || rl >= WIN_COUNT;
}
