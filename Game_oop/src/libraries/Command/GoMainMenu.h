#ifndef go_main_menu_h
#define go_main_menu_h

#include "Command/Command.h"
#include "Game/Engine/GameEngine.h"

class GoMainMenu : public Command {
public:
    void execute(GameEngine &game);
};

#endif