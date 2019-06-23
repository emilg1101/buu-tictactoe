#ifndef BUU_TICTACTOE_COMMANDHANDLER_H
#define BUU_TICTACTOE_COMMANDHANDLER_H

class CommandHandler {
public:
    CommandHandler() {}

    ~CommandHandler() {}

    virtual void newGame() = 0;

    virtual void exit() = 0;

    virtual void back() = 0;
};

#endif //BUU_TICTACTOE_COMMANDHANDLER_H
