#include "ChangeDifficulty.h"

ChangeDifficulty :: ChangeDifficulty() : difficulty_(DefaultLevelGenerator::DIFFICULTY::EASY) {}

ChangeDifficulty :: ChangeDifficulty(DefaultLevelGenerator::DIFFICULTY difficulty) : 
    difficulty_(difficulty) {}

void ChangeDifficulty :: execute(GameEngine &game) {
    game.change_difficulty(difficulty_);
}