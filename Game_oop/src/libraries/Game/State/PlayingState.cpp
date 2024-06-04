#include "PlayingState.h"
#include "Command/MovePlayer.h"
#include "Command/ExitGame.h"
#include "Command/GoMainMenu.h"

bool PlayingState :: execute_command(GameEngine &game, Command *command) {
    bool is_executed = false;
    if(typeid(*command) == typeid(MovePlayer) || typeid(*command) == typeid(ExitGame)
        || typeid(*command) == typeid(GoMainMenu)) {
        command->execute(game);
        is_executed = true;
    }

    return is_executed;
}