#include "FirstPlayer.h"

extern Display *display;

FirstPlayer::FirstPlayer(Display *_display) {
    display = _display;
}

Position FirstPlayer::getMove() {
    return display->getFirstPlayerMove();
}

void FirstPlayer::setMove(Position position) {

}
