#include <utility>

#include <fstream>
#include <iostream>
#include "Saver.h"

using namespace std;

string firstPlayerName;
string secondPlayerName;

string fileIsMultiPlayer = "isMultiPlayer.txt";
string fileField = "Field.txt";
string fileLastMovePlayer = "lastMovePlayer.txt";
string fileFirstPlayerName = "firstPlayerName.txt";
string fileSecondPlayerName = "secondPlayerName.txt";

Saver::Saver(string _firstPlayer, string _secondPlayer) {
    firstPlayerName = std::move(_firstPlayer);
    secondPlayerName = std::move(_secondPlayer);
}

void Saver::setIsMultiPlayer(bool isMultiPlayer) {
    Saver::isMultiPlayer = isMultiPlayer;
}

bool Saver::hasSavedGame() {
    return false;
}

Save Saver::getSave() {

    return Save(Field(), 0);
}

void Saver::newSave(Field field, int lastMovePlayer) {
//  save is multiplayer
    write(std::to_string(isMultiPlayer), fileIsMultiPlayer);

//  save last move player
    write(std::to_string(lastMovePlayer), fileLastMovePlayer);

//  save field
    saveField(field);

//  save first player' name()
    write(firstPlayerName, fileFirstPlayerName);

//  save second player' name
    write(secondPlayerName, fileSecondPlayerName);
}

void Saver::saveField(const Field &field) const {
    string toSave;
    for (int i = 0; i < field.size; ++i) {
        for (int j = 0; j < field.size; ++j) {
            toSave += to_string(field[i][j]);
        }
        toSave += "\n";
    }
    write(toSave, fileField);
}


void Saver::read() const {
    fstream fio;
    string line;

    // Execute a loop untill EOF (End of File)
    // point read pointer at beginning of file
    fio.seekg(0, ios::beg);

    while (fio) {

        // Read a Line from File
        getline(fio, line);

        // Print line in Console
        cout << line << endl;
    }

    // Close the file
    fio.close();
}

void Saver::write(string line, string &fileName) const {
    fstream file;

    //opening file "sample.txt" in out(write) mode
    file.open(fileName, ios_base::trunc | ios_base::out | ios_base::in);

    if (!file) {
        cout << "Error in creating file!!!" << endl;
    }

    file << line;
}

void Saver::deleteSave() {
    string emptyString;
    string fileName = "save.txt";
    write(emptyString, fileName);
}
