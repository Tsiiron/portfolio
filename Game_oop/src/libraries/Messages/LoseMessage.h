#ifndef lose_message_h
#define lose_message_h

#include "MessageInterface.h"
#include "Game/Engine/GameEngine.h"

class LoseMessage : public MessageInterface {
private:
    Coordinates coordinates_;
public:
    LoseMessage(GameEngine& game);
    std::string to_string() override;
};

#endif