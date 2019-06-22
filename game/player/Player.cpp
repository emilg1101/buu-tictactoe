#include "Player.h"

extern Display *display;
extern int type;

Player::Player(Display *_display, int _type) : PlayerIOStream(_type) {
    display = _display;
    type = _type;
}

Position Player::getMove() {
    if (type == CROSS_CELL_CODE) {
        return display->getFirstPlayerMove();
    }
    return display->getSecondPlayerMove();
}

void Player::setMove(Position position, int cellType) {

}
