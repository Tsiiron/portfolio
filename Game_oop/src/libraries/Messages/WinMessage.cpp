#include "WinMessage.h"

WinMessage :: WinMessage(GameEngine& game) : hp_(game.handler()->get_hp()), 
                                            score_(game.handler()->get_score()) 
                                            {}

std::string WinMessage :: to_string() {
    std::ostringstream ss;
    ss << "Вы выиграли!\n";
    ss << "Здоровье : " << hp_ << '\n';
    ss << "Очки : " << score_ << '\n';
    return ss.str();
}