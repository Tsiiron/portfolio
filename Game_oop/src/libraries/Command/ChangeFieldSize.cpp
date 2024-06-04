#include "ChangeFieldSize.h"

ChangeFieldSize :: ChangeFieldSize() : size_(DefaultLevelGenerator::MAP_SIZE::SMALL) {}

ChangeFieldSize :: ChangeFieldSize(DefaultLevelGenerator::MAP_SIZE size) : 
    size_(size) {}

void ChangeFieldSize :: execute(GameEngine &game) {
    game.resize_field(size_);
}