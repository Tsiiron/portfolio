#ifndef exit_game_h
#define exit_game_h

#include "Command/Command.h"
#include "Game/Engine/GameEngine.h"

class ExitGame : public Command {
public:
    void execute(GameEngine &game);
};

#endif