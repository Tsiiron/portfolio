#ifndef win_message_h
#define win_message_h

#include "MessageInterface.h"
#include "Game/Engine/GameEngine.h"

class WinMessage : public MessageInterface {
private:
    int32_t hp_;
    int32_t score_;
public:
    WinMessage(GameEngine& game);
    std::string to_string() override;
};

#endif