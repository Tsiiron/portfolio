#ifndef lose_state_h
#define lose_state_h

#include "GameState.h"
#include "Game/Engine/GameEngine.h"

class LoseState : public GameState {
public:
    bool execute_command(GameEngine &game, Command *command) override;
};

#endif