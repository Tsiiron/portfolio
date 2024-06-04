#include "DefaultLevelGenerator.h"
#include <iostream>

DefaultLevelGenerator :: DefaultLevelGenerator(MAP_SIZE size, DIFFICULTY difficulty) : size_(size), difficulty_(difficulty) {}

Field* DefaultLevelGenerator :: generate(PlayerHandler* handler) const {
    Dimension dimension;
    int32_t event;
    int32_t movement;
    int32_t negative;
    int32_t positive;
    int32_t enemies;

    switch(size_) {
        case MAP_SIZE::MEDIUM:
            dimension.set_x(30);
            dimension.set_y(20);
            break;
        case MAP_SIZE::HUGE:
            dimension.set_x(32);
            dimension.set_y(32);
            break;
        case MAP_SIZE::SMALL:
        default:
            dimension.set_x(20);
            dimension.set_y(20);
            break;
    }

    switch(difficulty_) {
        case DIFFICULTY::HARD:
            event = 35;
            movement = 25;
            negative = 50;
            positive = 25;
            enemies = 10;
            break;
        case DIFFICULTY::EASY:
        default:
            event = 20;
            movement = 25;
            negative = 25;
            positive = 50;
            enemies = 5;
    }
    Generator gen(dimension.get_x(), dimension.get_y(), event, movement, positive, negative, enemies);
    return gen.generate(handler);
}