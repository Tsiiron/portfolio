#include "NewGameMessage.h"

NewGameMessage :: NewGameMessage(GameEngine& game) : coordinates_(game.handler()->get_coordinates()),
                                                    dimensions_(game.handler()->get_dimensions())
                                                    {}

std::string NewGameMessage :: to_string() {
    std::ostringstream ss;
    ss << "Начата новая игра!\n";
    ss << "Размеры поля : { " << dimensions_.get_x() << " ; " << dimensions_.get_y() << " }\n";
    ss << "Текущие координаты : { " << coordinates_.get_x() << " ; " << coordinates_.get_y() << " }\n";
    return ss.str();
}