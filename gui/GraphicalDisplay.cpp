#include "GraphicalDisplay.h"

GraphicalDisplay::GraphicalDisplay(CommandHandler *_handler) {
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Test");
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }
    }
}

GraphicalDisplay::~GraphicalDisplay() {
}

Configuration GraphicalDisplay::getConfiguration() {
    return Configuration();
}

void GraphicalDisplay::drawField(Field field) {

}

Position GraphicalDisplay::getFirstPlayerMove() {
    return Position(0, 0);
}

Position GraphicalDisplay::getSecondPlayerMove() {
    return Position(0, 0);
}

void GraphicalDisplay::showWrongMove() {

}

void GraphicalDisplay::showWinner(int type) {

}

bool GraphicalDisplay::loadSavedGame() {
    return false;
}

void GraphicalDisplay::setFirstPlayerName(string name) {

}

void GraphicalDisplay::setSecondPlayerName(string name) {

}
