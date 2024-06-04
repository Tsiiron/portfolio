#ifndef logging_file_h
#define logging_file_h

#include "Command.h"
#include "Game/Engine/GameEngine.h"

class LoggingFile : public Command {
public:
    void execute(GameEngine &game);
};

#endif