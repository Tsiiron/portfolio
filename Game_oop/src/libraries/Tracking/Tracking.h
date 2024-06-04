#ifndef tracking_h
#define tracking_h

#include "Rendering/RenderingInterface.h"

class PlayerHandler;
class GameState;
class Command;

#include <string>

enum class Messages{Start, Exit, Restart, ChangeDifficulty, ChangeSize, Move, GoMainMenu, Win, Lose};

class Tracking{
private:
    PlayerHandler* handler_;
    RenderingInterface* rendering_;
public:
    Tracking(PlayerHandler* new_handler, std::string file_name);
    Tracking(PlayerHandler* new_handler, std::ostream &out);
    void update(GameState* state);
    void update(Command* command);
};

#endif