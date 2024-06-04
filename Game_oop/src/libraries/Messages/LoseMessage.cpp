#include "LoseMessage.h"

LoseMessage :: LoseMessage(GameEngine& game) : coordinates_(game.handler()->get_coordinates()) {}

std::string LoseMessage :: to_string() {
    std::ostringstream ss;
    ss << "Вы проиграли!\n";
    ss << "Текущие координаты : { " << coordinates_.get_x() << " ; " << coordinates_.get_y() << " }\n";
    return ss.str();
}