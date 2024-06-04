#include "MainMenuState.h"
#include "Command/ChangeDifficulty.h"
#include "Command/ChangeFieldSize.h"
#include "Command/StartGame.h"
#include "Command/ExitGame.h"
#include "Command/RestartGame.h"
#include "Command/LoggingFile.h"
#include "Command/LoggingStream.h"

bool MainMenuState :: execute_command(GameEngine &game, Command *command) {
    bool is_executed = false;
    if(typeid(*command) == typeid(ChangeDifficulty) || typeid(*command) == typeid(ChangeFieldSize)
        || typeid(*command) == typeid(StartGame) || typeid(*command) == typeid(ExitGame)
        || typeid(*command) == typeid(RestartGame) || typeid(*command) == typeid(LoggingFile)
        || typeid(*command) == typeid(LoggingStream))
    {
        command->execute(game);
        is_executed = true;
    }

    return is_executed;
}