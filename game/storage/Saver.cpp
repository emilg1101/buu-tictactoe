#include "Saver.h"

Saver::Saver() {}

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
