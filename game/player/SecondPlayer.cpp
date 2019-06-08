#include "SecondPlayer.h"

extern Display *display;

SecondPlayer::SecondPlayer(Display *_display) {
    display = _display;
}

Position SecondPlayer::getMove() {
    return display->getSecondPlayerMove();
}

void SecondPlayer::setField(Field field) {

}
