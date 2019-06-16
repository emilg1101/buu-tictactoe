#include "Saver.h"

Saver::Saver(bool _isMultiplayer, string _firstPlayer, string _secondPlayer) {

}

bool Saver::hasSavedGame() {
    return false;
}

Save Saver::getSave() {
    return Save(Field(), 0);
}

void Saver::newSave(Field field, int lastMovePlayer) {

}

void Saver::deleteSave() {

}
