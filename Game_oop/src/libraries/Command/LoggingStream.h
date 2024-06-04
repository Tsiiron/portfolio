#ifndef logging_stream_h
#define logging_stream_h

#include "Command.h"
#include "Game/Engine/GameEngine.h"

class LoggingStream : public Command {
public:
    void execute(GameEngine &game);
};

#endif