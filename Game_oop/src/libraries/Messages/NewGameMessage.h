#ifndef new_game_message_h
#define new_game_message_h

#include "MessageInterface.h"
#include "Game/Engine/GameEngine.h"

class NewGameMessage : public MessageInterface {
private:
    Coordinates coordinates_;
    Dimension dimensions_;
public:
    NewGameMessage(GameEngine& game);
    std::string to_string() override;
};

#endif