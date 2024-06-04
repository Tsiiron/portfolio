#ifndef wrong_command_message_h
#define wrong_command_message_h

#include "MessageInterface.h"
#include "Game/Engine/GameEngine.h"

class WrongCommandMessage : public MessageInterface {
private:
    char symb_;
public:
    WrongCommandMessage(char symb);
    std::string to_string() override;
};

#endif