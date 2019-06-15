#include <iostream>
#include <string.h>
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

string firstPlayerName;
string secondPlayerName;

bool isMultiPlayer;

const int MAX_FIELD_HEIGHT = 11;
const int MAX_FIELD_WIDTH = 11;
const int CONSOLE_WORKING_HEIGHT = 30;
const Coord START_TABLE_COORD = Coord(0, 1);
const Coord START_PLAYER_INPUT_COORD = Coord(0, 25);
const Coord START_MESSAGE_COORD = Coord(0, 24);

Coord currentCoord = Coord();

CONSOLE_SCREEN_BUFFER_INFO csbi;
HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
COORD destCoord;

int getAvailableColumns(){
    CONSOLE_SCREEN_BUFFER_INFO sbInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &sbInfo);
    int availableColumns = sbInfo.dwSize.X;
    return availableColumns;
}

void moveToSecondLineStartCoord(){
    destCoord.X = 0;
    destCoord.Y = 1;
    SetConsoleCursorPosition(hStdout, destCoord);
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
    destCoord.X = 0;
    destCoord.Y = 0;
    SetConsoleCursorPosition(hStdout, destCoord);
}

void removeMessage(){
    moveToMessageStartCoord();
    removeLineFromCurrentCoord();
}

void askIsMultiPlayer(){
    string mp;
    moveToSecondLineStartCoord();
    removeLineFromCurrentCoord();
    cout << "Is Multi Player Game[Y/N]: ";
    cin >> mp;
    if (mp.compare("Y") == 0 ){
        isMultiPlayer = true;
    } else if(mp.compare("N") == 0 ){
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

void askOneUserName(){
    cout << "Write player name: ";
    cin >> firstPlayerName;
    secondPlayerName = "Computer";
    moveToStartCoord();
    removeLineFromCurrentCoord();
    moveToStartCoord();
}

void askTwoUsersName(){
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

void cleanConsoleNoWorkingSpace(){
    destCoord.X = 0;
    for (int i = START_PLAYER_INPUT_COORD.y + 1; i < CONSOLE_WORKING_HEIGHT; i++){
        destCoord.Y = i;
        SetConsoleCursorPosition(hStdout, destCoord);
        removeLineFromCurrentCoord();
    }
    moveToStartCoord();
}

void showWrongMoveMessage(){
    cleanConsoleNoWorkingSpace();
    moveToMessageStartCoord();
    removeLineFromCurrentCoord();
    moveToMessageStartCoord();
    cout << "Wrong input!" << endl;
}

bool isInputPositionRight(string xStr, string yStr){
    try{
        int x = stoi(xStr);
        int y = stoi(yStr);
        if ((x > MAX_FIELD_WIDTH - 1) || (y > MAX_FIELD_HEIGHT - 1)){
            return false;
        }
    } catch (invalid_argument){
        return false;
    } catch (out_of_range){
        return false;
    }
    return true;
}

void ConsoleDisplay::showWrongMove() {
    showWrongMoveMessage();
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

ConsoleDisplay::ConsoleDisplay() {}

ConsoleDisplay::~ConsoleDisplay() {}

Configuration ConsoleDisplay::getConfiguration() {
    askIsMultiPlayer();
    if(isMultiPlayer){
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
    cout << "Game field:" << endl;
    moveToTableStartCoord();
    for (int i = 0; i <= MAX_FIELD_HEIGHT * 2; i++) {
        for (int j = 0; j <= MAX_FIELD_WIDTH * 2; j++) {
            if (i == 0 && j == 0){
                cout << char(218);
            } else if (i == 0 && j == MAX_FIELD_WIDTH * 2){
                cout << char(191);
            } else if (i == MAX_FIELD_HEIGHT * 2  && j == 0){
                cout << char(192);
            } else if (i == MAX_FIELD_HEIGHT * 2  && j == MAX_FIELD_WIDTH * 2) {
                cout << char(217);
            } else if ((i % 2 == 0) && (j % 2 == 1)) {
                cout << char(196);
            } else if ((i % 2 == 1) && (j % 2 == 0)) {
                cout << char(179);
            } else if (i == 0 && (j % 2 == 0) && j != 0 && j != MAX_FIELD_WIDTH * 2) {
                cout << char(194);
            } else if (i == MAX_FIELD_WIDTH * 2 && (j % 2 == 0) && j != 0 && j != MAX_FIELD_WIDTH * 2) {
                cout << char(193);
            } else if (j == 0 && (i % 2 == 0) && i != 0 && i != MAX_FIELD_WIDTH * 2) {
                cout << char(195);
            } else if (j == MAX_FIELD_WIDTH * 2 && (i % 2 == 0) && i != 0 && i != MAX_FIELD_WIDTH * 2) {
                cout << char(180);
            } else if ((i % 2 == 0) && (j % 2 == 0) && i != 0 && i != MAX_FIELD_WIDTH * 2 && j != 0 && j != MAX_FIELD_WIDTH * 2){
                cout << char(197);
            } else if ((i % 2 == 1) && (j % 2 == 1) && i != 0 && i != MAX_FIELD_WIDTH * 2 && j != 0 && j != MAX_FIELD_WIDTH * 2){
                if (field[j / 2][i / 2] == 1) {
                    cout << "X";
                } else if (field[j / 2][i / 2] == 2){
                    cout << "0";
                } else {
                    cout << " ";
                }
            }
        }
        cout << endl;
    }
}

Position ConsoleDisplay::getFirstPlayerMove() {
    moveToPlayerInputStartCoord();
    removeLineFromCurrentCoord();
    moveToPlayerInputStartCoord();
    cout << "<" << firstPlayerName << ">enter position: ";
    string xStr, yStr;
    cin >> xStr >> yStr;
    while(! isInputPositionRight(xStr, yStr)){
        showWrongMoveMessage();
        moveToPlayerInputStartCoord();
        removeLineFromCurrentCoord();
        moveToPlayerInputStartCoord();
        cout << "<" << firstPlayerName << ">enter position: ";
        cin >> xStr >> yStr;
    }
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
    while(! isInputPositionRight(xStr, yStr)){
        showWrongMoveMessage();
        moveToPlayerInputStartCoord();
        removeLineFromCurrentCoord();
        moveToPlayerInputStartCoord();
        cout << "<" << firstPlayerName << ">enter position: ";
        cin >> xStr >> yStr;
    }
    int x = stoi(xStr);
    int y = stoi(yStr);
    removeMessage();
    return Position(x, y);
}
