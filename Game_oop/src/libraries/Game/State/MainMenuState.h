#ifndef main_menu_state_h
#define main_menu_state_h

#include "GameState.h"
#include "Game/Engine/GameEngine.h"

class MainMenuState : public GameState {
public:
    bool execute_command(GameEngine &game, Command *command) override;
};

#endif