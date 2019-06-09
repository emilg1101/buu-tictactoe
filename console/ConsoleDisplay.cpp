#include <iostream>
#include "ConsoleDisplay.h"

using namespace std;

ConsoleDisplay::ConsoleDisplay() {}

ConsoleDisplay::~ConsoleDisplay() {}

Configuration ConsoleDisplay::getConfiguration() {
    Configuration configuration = Configuration();
    configuration.IS_MULTIPLAYER = true;
    return configuration;
}

void ConsoleDisplay::drawField(Field field) {
    cout << "Game field:" << endl;
    for (int i = 0; i < field.getSize(); i++) {
        for (int j = 0; j < field.getSize(); j++) {
            cout << field[i][j] << " ";
        }
        cout << endl;
    }
}

void ConsoleDisplay::showWrongMove() {
    cout << "Wrong input!" << endl;
}

void ConsoleDisplay::showWinner(int type) {

}

Position ConsoleDisplay::getFirstPlayerMove() {
    cout << "<Player1>enter position: ";
    int x, y;
    cin >> x >> y;
    return Position(x, y);
}

Position ConsoleDisplay::getSecondPlayerMove() {
    cout << "<Player2>enter position: ";
    int x, y;
    cin >> x >> y;
    return Position(x, y);
}
