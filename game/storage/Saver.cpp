#include <utility>

#include <fstream>
#include <iostream>
#include "Saver.h"

using namespace std;

string firstPlayerName;
string secondPlayerName;

string fileIsMultiPlayer = "saveIsMultiPlayer.txt";
string fileField = "saveField.txt";
string fileLastMovePlayer = "saveLastMovePlayer.txt";
string fileFirstPlayerName = "saveFirstPlayerName.txt";
string fileSecondPlayerName = "saveSecondPlayerName.txt";
string fileIsSaved = "saveIsSaved.txt";

Saver::Saver(string _firstPlayer, string _secondPlayer) {
    firstPlayerName = std::move(_firstPlayer);
    secondPlayerName = std::move(_secondPlayer);
}

void Saver::setIsMultiPlayer(bool isMultiPlayer) {
    Saver::isMultiPlayer = isMultiPlayer;
}

bool Saver::hasSavedGame() {
    bool b;
    string isMulti = read(fileIsMultiPlayer);

    if (isMulti != "") {
        b = static_cast<bool>(std::stoi(isMulti));
    } else {
        return 0;
    }

    return b;
}

Save Saver::getSave() {
    string nameFirst = read(fileFirstPlayerName);
    string lastMovePlayer = read(fileLastMovePlayer);
    Field savedField = readField(fileField);
    cout << nameFirst;
    return Save(savedField, std::stoi(read(fileLastMovePlayer)));
}

void Saver::newSave(Field field, int lastMovePlayer) {

//  mark that game is saved
    write("1", fileIsSaved);

//  save is multiplayer
    write(std::to_string(lastMovePlayer), fileIsMultiPlayer);

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
            toSave += field[i][j];
        }
    }
    write(toSave, fileField);
}

string Saver::read(string &fileName) const {
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

    //opening file "sample.txt" in out(write) mode
    file.open(fileName, ios_base::trunc | ios_base::out | ios_base::in);

    if (!file) {
        cout << "Error in creating file!!!";
    }

    file << line;

    file.close();
}

void Saver::deleteSave() {
    write("0", fileIsSaved);
}

Field Saver::readField(string fileName) {
    ifstream fin;
    fin.open(fileName, ios::in);
    Field field = Field(11);

    char my_character;
    int number_of_lines = 0;

    for (int i = 0; i < 11; ++i) {
        for (int j = 0; j < 11; ++j) {
            fin.get(my_character);
            cout << my_character;
            field[i][j] = my_character;
        }
    }
}
