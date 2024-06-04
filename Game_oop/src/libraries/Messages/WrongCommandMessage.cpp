#include "WrongCommandMessage.h"

WrongCommandMessage :: WrongCommandMessage(char symb) : symb_(symb) {}

std::string WrongCommandMessage :: to_string() {
    std::ostringstream ss;
    ss << "Был введён неправильный символ [" << symb_ << "] ! Команда не выполнена!\n";
    return ss.str();
}