#ifndef command_h
#define command_h

class GameEngine;

class Command {
public:
    virtual ~Command() = default;
    virtual void execute(GameEngine &game) = 0;
};

#endif