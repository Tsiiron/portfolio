#ifndef game_state_h
#define game_state_h

class GameEngine;
#include "Command/Command.h"

class GameState {
public:
    virtual ~GameState() = default;
    virtual bool execute_command(GameEngine &game, Command *command) = 0;
};

#endif