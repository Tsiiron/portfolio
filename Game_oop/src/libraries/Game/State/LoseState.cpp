#include "LoseState.h"
#include "Command/ExitGame.h"
#include "Command/RestartGame.h"
#include "Command/GoMainMenu.h"

bool LoseState :: execute_command(GameEngine &game, Command *command) {
    bool is_executed = false;
    if(typeid(*command) == typeid(ExitGame) || typeid(*command) == typeid(RestartGame)
            || typeid(*command) == typeid(GoMainMenu)) {
        command->execute(game);
        is_executed = true;
    }

    return is_executed;
}