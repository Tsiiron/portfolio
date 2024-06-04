#ifndef correct_command_message_h
#define correct_command_message_h

#include "MessageInterface.h"
#include "Game/Engine/GameEngine.h"

class CorrectCommandMessage : public MessageInterface {
private:
    char symb_;
    std::string command_name_;
public:
    CorrectCommandMessage(char symb, std::string command_name);
    std::string to_string() override;
};

#endif