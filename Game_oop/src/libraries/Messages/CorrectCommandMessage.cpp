#include "CorrectCommandMessage.h"

CorrectCommandMessage :: CorrectCommandMessage(char symb, std::string command_name) : 
                                    symb_(symb),
                                    command_name_(command_name)
                                    {}

std::string CorrectCommandMessage :: to_string() {
    std::ostringstream ss;
    ss << "Был введён символ [" << symb_ << "]\n";
    ss << "Сработала команда : " << command_name_ << '\n';
    return ss.str();
}
