#ifndef playing_state_h
#define playing_state_h

#include "GameState.h"
#include "Game/Engine/GameEngine.h"

class PlayingState : public GameState {
public:
    bool execute_command(GameEngine &game, Command *command) override;
};

#endif