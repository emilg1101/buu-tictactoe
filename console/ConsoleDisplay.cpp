#include <iostream>
#include <windows.h>
#include "ConsoleDisplay.h"

using namespace std;

int currentCoordX;
int currentCoordY;

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

void moveToMessageCoord() {
    destCoord.X = 0;
    destCoord.Y = 12;
    SetConsoleCursorPosition(hStdout, destCoord);
}

void saveCurrentCoord() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(
            GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        currentCoordX = csbi.dwCursorPosition.X;
        currentCoordY = csbi.dwCursorPosition.Y;
    } else {
        currentCoordX = 0;
        currentCoordY = 0;
    }
}

void moveToCurrentCoord() {
    destCoord.X = currentCoordX;
    destCoord.Y = currentCoordY;
    SetConsoleCursorPosition(hStdout, destCoord);
}

void removePreviousLine() {
    saveCurrentCoord();
    cout << "                                                                  ";
    moveToCurrentCoord();
}

void moveToStartCoord() {
    destCoord.X = 0;
    destCoord.Y = 1;
    SetConsoleCursorPosition(hStdout, destCoord);
}

void ConsoleDisplay::drawField(Field field) {
    moveToStartCoord();
    cout << "Game field:" << endl;
    for (int i = 0; i < field.getSize(); i++) {
        for (int j = 0; j < field.getSize(); j++) {
            cout << field[i][j] << " ";
        }
        cout << endl;
    }
    moveToMessageCoord();
}

void ConsoleDisplay::showWrongMove() {
    removePreviousLine();
    cout << "Wrong input!" << endl;
}

void ConsoleDisplay::showWinner(int type) {
    removePreviousLine();
    if (type == 0) {
        cout << "First player win";
    } else if (type == 1) {
        cout << "Second player win";
    } else {
        cout << "Draw";
    }
}

Position ConsoleDisplay::getFirstPlayerMove() {
    removePreviousLine();
    cout << "<Player1>enter position: ";
    int x, y;
    cin >> x >> y;
    return Position(x, y);
}

Position ConsoleDisplay::getSecondPlayerMove() {
    removePreviousLine();
    cout << "<Player2>enter position: ";
    int x, y;
    cin >> x >> y;
    return Position(x, y);
}
