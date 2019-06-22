#include <utility>

#include <fstream>
#include <iostream>
#include "Saver.h"

using namespace std;

extern string firstPlayerName;
extern string secondPlayerName;

string fileIsMultiPlayer = "saveIsMultiPlayer.txt";
string fileField = "saveField.txt";
string fileFirstPlayerName = "saveFirstPlayerName.txt";
string fileSecondPlayerName = "saveSecondPlayerName.txt";
string fileLastMovePlayer = "saveLastMovePlayer.txt";
string fileIsSaved = "saveIsSaved.txt";

void Saver::setIsMultiPlayer(bool isMultiPlayer) {
    Saver::isMultiPlayer = isMultiPlayer;
}

bool Saver::hasSavedGame() {
    string isMulti = readLineFromFile(fileIsSaved);

    if (!isMulti.empty()) {
        return static_cast<bool>(std::stoi(isMulti));
    } else {
        return false;
    }
}

Save Saver::getSave() {
    string nameFirst = readLineFromFile(fileFirstPlayerName);
    string nameSecond = readLineFromFile(fileSecondPlayerName);
    string lastMovePlayer = readLineFromFile(fileLastMovePlayer);
    string isMultiPlayer = readLineFromFile(fileIsMultiPlayer);
    Field savedField = readField();

    Save save = Save();
    save.field = savedField;
    save.firstPlayer = nameFirst;
    save.secondPlayer = nameSecond;
    save.lastMovePlayer = std::stoi(lastMovePlayer);
    save.isMultiplayer = std::stoi(isMultiPlayer);

    return save;
}

void Saver::newSave(Field field, int lastMovePlayer) {

//  mark that game is saved
    write("1", fileIsSaved);

//  save is multiplayer
    write(std::to_string(isMultiPlayer), fileIsMultiPlayer);

//  save last move player
    write(std::to_string(lastMovePlayer), fileLastMovePlayer);

//  save field
    saveField(field);

//  save first player' name
    write(firstPlayerName, fileFirstPlayerName);

//  save second player' name
    write(secondPlayerName, fileSecondPlayerName);
}

void Saver::saveField(const Field &field) const {
    string toSave;
    for (int i = 0; i < field.size; ++i) {
        for (int j = 0; j < field.size; ++j) {
            toSave += field[i][j];
        }
    }
    write(toSave, fileField);
}

string Saver::readLineFromFile(string &fileName) const {
    ifstream fin;
    string line;

    // by default open mode = ios::in mode
    fin.open(fileName);

    // Execute a loop until EOF (End of File)
    while (fin) {
        // Read a Line from File
        getline(fin, line);
    }

    // Close the file
    fin.close();

    return line;
}

void Saver::write(string line, string &fileName) const {
    fstream file;

    file.open(fileName, ios_base::trunc | ios_base::out | ios_base::in);

    if (!file) {
        cout << "Error in creating file";
    }

    file << line;

    file.close();
}

void Saver::deleteSave() {
    write("0", fileIsSaved);
}

Field Saver::readField() const {
    ifstream fin;
    fin.open(fileField, ios::in);
    Field field = Field(11);

    char my_character;

    for (int i = 0; i < 11; ++i) {
        for (int j = 0; j < 11; ++j) {
            fin.get(my_character);
            cout << my_character;
            field[i][j] = my_character;
        }
    }

    return field;
}

void Saver::setFirstPlayerName(string name) {
    firstPlayerName = name;
}

void Saver::setSecondPlayerName(string name) {
    secondPlayerName = name;
}
