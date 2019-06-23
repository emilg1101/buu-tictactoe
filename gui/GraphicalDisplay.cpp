#include <iostream>
#include "GraphicalDisplay.h"

const int ACTION_NEW_GAME = 0;
const int ACTION_MODE_REQUEST = 1;

struct GameEvent {
    int action;
    Position position;
    string text;
};

class GameField : public sf::Drawable, public sf::Transformable {
public:
    Field field;

    GameField(Field _field) {
        field = _field;
    }

    string getChar(int cellType) const {
        if (cellType == CROSS_CELL_CODE) {
            return "x";
        } else if (cellType == CIRCLE_CELL_CODE) {
            return "o";
        }
        return "";
    }

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        sf::Font font;
        font.loadFromFile("arial.ttf");
        states.transform *= getTransform();
        sf::Color color = sf::Color(200, 100, 200);

        sf::RectangleShape shape(sf::Vector2f(550, 550));
        shape.setOutlineThickness(2.f);
        shape.setOutlineColor(color);
        shape.setFillColor(sf::Color::Transparent);
        target.draw(shape, states);

        sf::Text text("", font, 45);

        sf::RectangleShape line(sf::Vector2f(550, 0));
        line.setOutlineThickness(1.f);
        line.setOutlineColor(color);

        for (int i = 1; i <= field.getSize() - 1; i++) {
            sf::Vector2f verticalPosition(i * 50, 0);
            line.setPosition(verticalPosition);
            line.rotate(90);
            target.draw(line, states);

            sf::Vector2f horizontalPosition(0, i * 50);
            line.setPosition(horizontalPosition);
            line.rotate(-90);
            target.draw(line, states);
        }

        for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 11; j++) {
                std::cout << field[i][j] << " ";
            }
            std::cout << std::endl;
        }

        for (int i = 0; i < field.getSize(); i++) {
            for (int j = 0; j < field.getSize(); j++) {
                text.setFillColor(color);
                text.setString(getChar(field[i][j]));

                sf::Vector2f textPosition((i * 50.f + 25.f) - (text.getGlobalBounds().width / 2),
                                          (j * 50.f + 25.f) - (text.getGlobalBounds().height / 2) -
                                          text.getLocalBounds().top);
                text.setPosition(textPosition);
                target.draw(text, states);
            }
        }
    }
};

sf::RenderWindow window;
extern CommandHandler *handler;
int nextMove = CROSS_CELL_CODE;

Position getPositionFromEvent(int x, int y) {
    if (x >= 0 && x <= 550 && y >= 0 && y <= 550) {
        return Position(x / 50, y / 50);
    }
    return Position(-1, -1);
}

Position listen() {
    sf::Event event;

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::F2) {
                        handler->newGame();
                    }
                    if (event.key.code == sf::Keyboard::F5) {
                        handler->back();
                    }
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        std::cout << "the right button was pressed" << std::endl;
                        std::cout << "mouse x: " << event.mouseButton.x - 50 << std::endl;
                        std::cout << "mouse y: " << event.mouseButton.y - 50 << std::endl;
                        Position position = getPositionFromEvent(event.mouseButton.x - 50, event.mouseButton.y - 50);
                        if (position.y != -1) {
                            return position;
                        }
                    }
                default:
                    break;
            }
        }
    }
}

string fPlayerName;
string sPlayerName;

bool requireYesNo() {
    sf::Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Y) {
                        return true;
                    }
                    if (event.key.code == sf::Keyboard::N) {
                        return false;
                    }
                default:
                    break;
            }
        }
    }
}

string requireText(string text) {
    sf::Font font;
    font.loadFromFile("arial.ttf");

    sf::Text inputText(text, font, 20);
    inputText.setFillColor(sf::Color::Cyan);
    inputText.setPosition(5.f, 5.f);

    sf::Event event;
    string s;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::TextEntered:
                    if (event.text.unicode == 8 && !s.empty()) {
                        s = s.substr(0, s.size() - 1);
                        std::cout << s << std::endl;
                    } else if (event.text.unicode == 13) {
                        window.clear();
                        return s;
                    } else if (event.text.unicode < 128) {
                        s.push_back((char) event.text.unicode);
                        std::cout << s << std::endl;
                    }
                default:
                    break;
            }
        }
        sf::Text text(s, font, 20);
        text.setFillColor(sf::Color::Cyan);
        text.setPosition(5.f, 25.f);
        window.clear();
        window.draw(text);
        window.draw(inputText);
        window.display();
    }
}

GraphicalDisplay::GraphicalDisplay(CommandHandler *_handler) {
    handler = _handler;
    window.create(sf::VideoMode(650, 700), "Tic tac toe");
    window.setFramerateLimit(60);
}

GraphicalDisplay::~GraphicalDisplay() {
}

Configuration GraphicalDisplay::getConfiguration() {
    sf::Font font;
    font.loadFromFile("arial.ttf");

    sf::Text text("Is Multi Player Game? [Y/N]", font, 20);
    text.setFillColor(sf::Color::Cyan);
    text.setPosition(5.f, 5.f);
    window.clear();
    window.draw(text);
    window.display();
    bool isMultiplayer = requireYesNo();

    if (isMultiplayer) {
        fPlayerName = requireText("Write 1 player name:");
        sPlayerName = requireText("Write 2 player name:");
    } else {
        fPlayerName = requireText("Write player name:");
        sPlayerName = "Computer";
    }
    Configuration configuration = Configuration();
    configuration.IS_MULTIPLAYER = isMultiplayer;
    window.clear();
    window.display();
    return configuration;
}

void GraphicalDisplay::drawField(Field field) {
    sf::Font font;
    font.loadFromFile("arial.ttf");

    sf::Text text("F2 - New Game / F5 - Move Back (only single player mode)", font, 20);
    text.setFillColor(sf::Color::Cyan);
    text.setPosition(5.f, 5.f);

    GameField gameField = GameField(field);
    gameField.setPosition(50.f, 50.f);

    sf::Text moveText("", font, 30);
    if (nextMove == CROSS_CELL_CODE) {
        moveText.setString(fPlayerName + " move!");
        nextMove = CIRCLE_CELL_CODE;
    } else {
        moveText.setString(sPlayerName + " move!");
        nextMove = CROSS_CELL_CODE;
    }
    moveText.setFillColor(sf::Color::Red);
    moveText.setPosition(325 - moveText.getGlobalBounds().width / 2, 650 - moveText.getGlobalBounds().height - 10);

    window.clear();
    window.draw(gameField);
    window.draw(text);
    window.draw(moveText);
    window.display();
    std::cout << "draw" << std::endl;
}

Position GraphicalDisplay::getFirstPlayerMove() {
    return listen();
}

Position GraphicalDisplay::getSecondPlayerMove() {
    return listen();
}

void GraphicalDisplay::showWrongMove() {}

void GraphicalDisplay::showWinner(int type) {
    string winningText;
    if (type == CROSS_CELL_CODE) {
        winningText = fPlayerName + " win!";
    } else if (type == CIRCLE_CELL_CODE) {
        winningText = sPlayerName + " win!";
    } else {
        winningText = "Draw!";
    }

    sf::Font font;
    font.loadFromFile("arial.ttf");

    sf::Text text(winningText, font, 30);
    text.setFillColor(sf::Color::Cyan);
    text.setPosition(325 - text.getGlobalBounds().width / 2, 325 - text.getGlobalBounds().height / 2);

    window.clear();
    window.draw(text);
    window.display();

    sf::Event event;

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::F2) {
                        handler->newGame();
                        return;
                    }
                default:
                    break;
            }
        }
    }
}

bool GraphicalDisplay::loadSavedGame() {
    sf::Font font;
    font.loadFromFile("arial.ttf");

    sf::Text text("You have saved game. Continue? [Y/N]", font, 20);
    text.setFillColor(sf::Color::Cyan);
    text.setPosition(5.f, 5.f);
    window.clear();
    window.draw(text);
    window.display();

    return requireYesNo();
}

void GraphicalDisplay::setFirstPlayerName(string name) {
    fPlayerName = name;
}

void GraphicalDisplay::setSecondPlayerName(string name) {
    sPlayerName = name;
}

string GraphicalDisplay::getFirstPlayerName() {
    return fPlayerName;
}

string GraphicalDisplay::getSecondPlayerName() {
    return sPlayerName;
}
