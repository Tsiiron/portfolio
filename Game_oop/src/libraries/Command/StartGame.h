#ifndef start_game_h
#define start_game_h

#include "Command/Command.h"
#include "Game/Engine/GameEngine.h"

class StartGame : public Command {
public:
    void execute(GameEngine &game);
};

#endif