#include <iostream>
#include <windows.h>
#include "ConsoleDisplay.h"

using namespace std;

struct Coord{
    int x;
    int y;
    Coord(){};
    Coord(int _x, int _y){
        x = _x;
        y = _y;
    }
};

const Coord START_COORD = Coord(0,0);
const Coord START_TABLE_COORD = Coord(0, 1);
const Coord START_PLAYER_INPUT_COORD = Coord(0, 13);
const Coord START_MESSAGE_COORD = Coord(0, 12);

Coord currentCoord = Coord();

CONSOLE_SCREEN_BUFFER_INFO csbi;
HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
COORD destCoord;

ConsoleDisplay::ConsoleDisplay() {}

ConsoleDisplay::~ConsoleDisplay() {}

Configuration ConsoleDisplay::getConfiguration() {

    Configuration configuration = Configuration();
    configuration.IS_MULTIPLAYER = true;
    return configuration;
}

int getAvailableColumns(){
    CONSOLE_SCREEN_BUFFER_INFO sbInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &sbInfo);
    int availableColumns = sbInfo.dwSize.X;
    return availableColumns;
}

void moveToTableStartCoord(){
    destCoord.X = START_TABLE_COORD.x;
    destCoord.Y = START_TABLE_COORD.y;
    SetConsoleCursorPosition(hStdout, destCoord);
}

void moveToMessageStartCoord() {
    destCoord.X = START_MESSAGE_COORD.x;
    destCoord.Y = START_MESSAGE_COORD.y;
    SetConsoleCursorPosition(hStdout, destCoord);
}

void moveToPlayerInputStartCoord(){
    destCoord.X = START_PLAYER_INPUT_COORD.x;
    destCoord.Y = START_PLAYER_INPUT_COORD.y;
    SetConsoleCursorPosition(hStdout, destCoord);
}

void saveCurrentCoord() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(
            GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        currentCoord.x = csbi.dwCursorPosition.X;
        currentCoord.y = csbi.dwCursorPosition.Y;
    } else {
        currentCoord.x = 0;
        currentCoord.y = 0;
    }
}

void moveToCurrentCoord() {
    destCoord.X = currentCoord.x;
    destCoord.Y = currentCoord.y;
    SetConsoleCursorPosition(hStdout, destCoord);
}

void removeLineFromCurrentCoord(){
    saveCurrentCoord();
    for(int i = 0; i < getAvailableColumns(); i++){
        cout << " ";
    }
    moveToCurrentCoord();
}

void moveToStartCoord() {
    destCoord.X = START_COORD.x;
    destCoord.Y = START_COORD.y;
    SetConsoleCursorPosition(hStdout, destCoord);
}

void removeMessage(){
    moveToMessageStartCoord();
    removeLineFromCurrentCoord();
}

void ConsoleDisplay::drawField(Field field) {
    moveToStartCoord();
    removeLineFromCurrentCoord();
    moveToStartCoord();
    cout << "Game field:" << endl;
    moveToTableStartCoord();
    for (int i = 0; i < field.getSize(); i++) {
        for (int j = 0; j < field.getSize(); j++) {
            cout << field[j][i] << " ";
        }
        cout << endl;
    }
}

void ConsoleDisplay::showWrongMove() {
    moveToMessageStartCoord();
    removeLineFromCurrentCoord();
    moveToMessageStartCoord();
    cout << "Wrong input!" << endl;
}

void ConsoleDisplay::showWinner(int type) {
    moveToMessageStartCoord();
    removeLineFromCurrentCoord();
    moveToMessageStartCoord();
    if (type == 0) {
        cout << "First player win";
    } else if (type == 1) {
        cout << "Second player win";
    } else {
        cout << "Draw";
    }
}

Position ConsoleDisplay::getFirstPlayerMove() {
    moveToPlayerInputStartCoord();
    removeLineFromCurrentCoord();
    moveToPlayerInputStartCoord();
    cout << "<Player1>enter position: ";
    int x, y;
    cin >> x >> y;
    removeMessage();
    return Position(x, y);
}

Position ConsoleDisplay::getSecondPlayerMove() {
    moveToPlayerInputStartCoord();
    removeLineFromCurrentCoord();
    moveToPlayerInputStartCoord();
    cout << "<Player2>enter position: ";
    int x, y;
    cin >> x >> y;
    removeMessage();
    return Position(x, y);
}
