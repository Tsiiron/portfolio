#ifndef move_player_h
#define move_player_h

#include "Command/Command.h"
#include "Game/Engine/GameEngine.h"

class MovePlayer : public Command {
private:
    const PlayerHandler::Direction direction_;
public:
    MovePlayer(PlayerHandler::Direction direction);
    void execute(GameEngine &game);
};

#endif