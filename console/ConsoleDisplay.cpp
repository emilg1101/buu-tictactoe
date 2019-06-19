#include <iostream>
#include <string.h>
#include <windows.h>
#include "ConsoleDisplay.h"

using namespace std;

struct Coord {
    int x;
    int y;

    Coord() {};

    Coord(int _x, int _y) {
        x = _x;
        y = _y;
    }
};

string firstPlayerName;
string secondPlayerName;

bool isMultiPlayer;

const char LEFT_TOP_EDGE = char(218);
const char RIGHT_TOP_EDGE = char(191);
const char LEFT_BOT_EDGE = char(192);
const char RIGHT_BOT_EDGE = char(217);
const char HORIZONTAL = char(196);
const char VERTICAL = char(179);
const char HEAD = char(194);
const char STAND = char(193);
const char LEFT_SERIF = char(195);
const char RIGHT_SERIF = char(180);
const char CROSS = char(197);


const int MAX_FIELD_HEIGHT = 11;
const int MAX_FIELD_WIDTH = 11;
const int CONSOLE_WORKING_HEIGHT = 30;
const int SYMBOL_LOWER_A_ASCI = 97;
const int SYMBOL_UPPER_A_ASCI = 65;
const Coord START_TABLE_COORD = Coord(0, 0);
const Coord START_PLAYER_INPUT_COORD = Coord(0, 25);
const Coord START_MESSAGE_COORD = Coord(0, 24);

Coord currentCoord = Coord();

CONSOLE_SCREEN_BUFFER_INFO csbi;
HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
COORD destCoord;

int getAvailableColumns() {
    CONSOLE_SCREEN_BUFFER_INFO sbInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &sbInfo);
    int availableColumns = sbInfo.dwSize.X;
    return availableColumns;
}

void moveToSecondLineStartCoord() {
    destCoord.X = 0;
    destCoord.Y = 1;
    SetConsoleCursorPosition(hStdout, destCoord);
}

void moveToTableStartCoord() {
    destCoord.X = START_TABLE_COORD.x;
    destCoord.Y = START_TABLE_COORD.y;
    SetConsoleCursorPosition(hStdout, destCoord);
}

void moveToMessageStartCoord() {
    destCoord.X = START_MESSAGE_COORD.x;
    destCoord.Y = START_MESSAGE_COORD.y;
    SetConsoleCursorPosition(hStdout, destCoord);
}

void moveToPlayerInputStartCoord() {
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

void removeLineFromCurrentCoord() {
    saveCurrentCoord();
    for (int i = 0; i < getAvailableColumns(); i++) {
        cout << " ";
    }
    moveToCurrentCoord();
}

void moveToStartCoord() {
    destCoord.X = 0;
    destCoord.Y = 0;
    SetConsoleCursorPosition(hStdout, destCoord);
}

void removeMessage() {
    moveToMessageStartCoord();
    removeLineFromCurrentCoord();
}

void askIsMultiPlayer() {
    string mp;
    moveToSecondLineStartCoord();
    removeLineFromCurrentCoord();
    cout << "Is Multi Player Game[Y/N]: ";
    cin >> mp;
    if (mp.compare("Y") == 0) {
        isMultiPlayer = true;
    } else if (mp.compare("N") == 0) {
        isMultiPlayer = false;
    } else {
        moveToStartCoord();
        cout << "Write only \"Y\" or \"N\" please";
        askIsMultiPlayer();
    }
    moveToStartCoord();
    removeLineFromCurrentCoord();
    moveToSecondLineStartCoord();
    removeLineFromCurrentCoord();
    moveToStartCoord();
}

void askOneUserName() {
    cout << "Write player name: ";
    cin >> firstPlayerName;
    secondPlayerName = "Computer";
    moveToStartCoord();
    removeLineFromCurrentCoord();
    moveToStartCoord();
}

void askTwoUsersName() {
    cout << "Write 1 player name: ";
    cin >> firstPlayerName;
    cout << "Write 2 player name: ";
    cin >> secondPlayerName;
    moveToStartCoord();
    removeLineFromCurrentCoord();
    moveToSecondLineStartCoord();
    removeLineFromCurrentCoord();
    moveToStartCoord();
}

void cleanConsoleNoWorkingSpace() {
    destCoord.X = 0;
    for (int i = START_PLAYER_INPUT_COORD.y + 1; i < CONSOLE_WORKING_HEIGHT; i++) {
        destCoord.Y = i;
        SetConsoleCursorPosition(hStdout, destCoord);
        removeLineFromCurrentCoord();
    }
    moveToStartCoord();
}

void showWrongMoveMessage() {
    cleanConsoleNoWorkingSpace();
    moveToMessageStartCoord();
    removeLineFromCurrentCoord();
    moveToMessageStartCoord();
    cout << "Wrong input!" << endl;
}

bool isInputPositionRight(string xStr, string yStr) {
    try {
        char *xCh = new char[xStr.length()];
        strcpy(xCh, xStr.c_str());
        if (xStr.length() > 1) {
            return false;
        }
        int x = int(xCh[0]);
        if (!(x >= 65 && x <= 75) && !(x >= 97 && x <= 107)) {
            return false;
        }
        int y = stoi(yStr);
        if (y > MAX_FIELD_WIDTH || y < 1) {
            return false;
        }
    } catch (invalid_argument) {
        return false;
    } catch (out_of_range) {
        return false;
    }
    return true;
}

void setNormalizePoint(string *xStr, string *yStr) {
    char *xCh = new char[xStr->length()];
    strcpy(xCh, xStr->c_str());
    int x = int(xCh[0]);
    if (x >= 97 && x <= 107) {
        x -= 97;
    } else if (x >= 65 && x <= 75) {
        x -= 65;
    }
    *xStr = to_string(x);
    *yStr = to_string(stoi(*yStr) - 1);
}

void tableDraw(Field field) {
    cout << " ";
    for (int i = 0; i < MAX_FIELD_WIDTH; i++) {
        cout << "   " << char(int('A') + i);
    }
    cout << endl;
    for (int i = 0; i <= MAX_FIELD_HEIGHT * 2; i++) {
        if (i % 2 == 1) {
            if (i / 2 + 1 < 10) {
                cout << " " << i / 2 + 1;
            } else {
                cout << i / 2 + 1;
            }
        } else {
            cout << "  ";
        }
        for (int j = 0; j <= MAX_FIELD_WIDTH * 4; j++) {
            if (i == 0) {
                if (j == 0) {
                    cout << LEFT_TOP_EDGE;
                } else if (j == MAX_FIELD_WIDTH * 4) {
                    cout << RIGHT_TOP_EDGE;
                } else if (j % 4 == 0) {
                    cout << HEAD;
                } else {
                    cout << HORIZONTAL;
                }
            } else if (i == MAX_FIELD_HEIGHT * 2) {
                if (j == 0) {
                    cout << LEFT_BOT_EDGE;
                } else if (j == MAX_FIELD_WIDTH * 4) {
                    cout << RIGHT_BOT_EDGE;
                } else if (j % 4 == 0) {
                    cout << STAND;
                } else {
                    cout << HORIZONTAL;
                }
            } else if (i % 2 == 0) {
                if (j == 0) {
                    cout << LEFT_SERIF;
                } else if (j == MAX_FIELD_WIDTH * 4) {
                    cout << RIGHT_SERIF;
                } else if (j % 4 == 0) {
                    cout << CROSS;
                } else {
                    cout << HORIZONTAL;
                }
            } else {
                if (j % 4 == 0) {
                    cout << VERTICAL;
                } else if (j % 2 == 0) {
                    if (field[j / 4][(i - 1) / 2] == 1) {
                        cout << "X";
                    } else if (field[j / 4][(i - 1) / 2] == 2) {
                        cout << "O";
                    } else {
                        cout << " ";
                    }
                } else {
                    cout << " ";
                }
            }
        }
        cout << endl;
    }
}

void ConsoleDisplay::showWrongMove() {
    showWrongMoveMessage();
}

void ConsoleDisplay::showWinner(int type) {
    moveToMessageStartCoord();
    removeLineFromCurrentCoord();
    moveToMessageStartCoord();
    if (type == 0) {
        cout << secondPlayerName << " win";
    } else if (type == 1) {
        cout << firstPlayerName<< " win";
    } else {
        cout << "Draw";
    }
}

ConsoleDisplay::ConsoleDisplay() {}

ConsoleDisplay::~ConsoleDisplay() {}

Configuration ConsoleDisplay::getConfiguration() {
    askIsMultiPlayer();
    if (isMultiPlayer) {
        askTwoUsersName();
    } else {
        askOneUserName();
    }
    Configuration configuration = Configuration();
    configuration.IS_MULTIPLAYER = true;
    return configuration;
}

void ConsoleDisplay::drawField(Field field) {
    cleanConsoleNoWorkingSpace();
    moveToStartCoord();
    removeLineFromCurrentCoord();
    moveToStartCoord();
    moveToTableStartCoord();
    tableDraw(field);
}

Position ConsoleDisplay::getFirstPlayerMove() {
    moveToPlayerInputStartCoord();
    removeLineFromCurrentCoord();
    moveToPlayerInputStartCoord();
    cout << "<" << firstPlayerName << ">enter position: ";
    string xStr, yStr;
    cin >> xStr >> yStr;
    while (!isInputPositionRight(xStr, yStr)) {
        showWrongMoveMessage();
        moveToPlayerInputStartCoord();
        removeLineFromCurrentCoord();
        moveToPlayerInputStartCoord();
        cout << "<" << firstPlayerName << ">enter position: ";
        cin >> xStr >> yStr;
    }
    setNormalizePoint(&xStr, &yStr);
    int x = stoi(xStr);
    int y = stoi(yStr);
    removeMessage();
    return Position(x, y);
}

Position ConsoleDisplay::getSecondPlayerMove() {
    moveToPlayerInputStartCoord();
    removeLineFromCurrentCoord();
    moveToPlayerInputStartCoord();
    cout << "<" << secondPlayerName << ">enter position: ";
    string xStr, yStr;
    cin >> xStr >> yStr;
    while (!isInputPositionRight(xStr, yStr)) {
        showWrongMoveMessage();
        moveToPlayerInputStartCoord();
        removeLineFromCurrentCoord();
        moveToPlayerInputStartCoord();
        cout << "<" << firstPlayerName << ">enter position: ";
        cin >> xStr >> yStr;
    }
    setNormalizePoint(&xStr, &yStr);
    int x = stoi(xStr);
    int y = stoi(yStr);
    removeMessage();
    return Position(x, y);
}
