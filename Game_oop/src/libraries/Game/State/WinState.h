#ifndef win_state_h
#define win_state_h

#include "GameState.h"
#include "Game/Engine/GameEngine.h"

class WinState : public GameState {
public:
    bool execute_command(GameEngine &game, Command *command) override;
};

#endif