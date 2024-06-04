#ifndef end_state_h
#define end_state_h

#include "GameState.h"
#include "Game/Engine/GameEngine.h"

class EndState : public GameState {
public:
    bool execute_command(GameEngine &game, Command *command) override;
};

#endif