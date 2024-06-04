#ifndef restart_game_h
#define restart_game_h

#include "Command/Command.h"
#include "Game/Engine/GameEngine.h"

class RestartGame : public Command {
public:
    void execute(GameEngine &game);
};

#endif