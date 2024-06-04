#ifndef change_difficilty_h
#define change_difficilty_h

#include "Command/Command.h"
#include "Game/Engine/GameEngine.h"
#include "FieldGenerator/DefaultLevels/DefaultLevelGenerator.h"

class ChangeDifficulty : public Command {
private:
    DefaultLevelGenerator::DIFFICULTY difficulty_;
public:
    ChangeDifficulty();
    ChangeDifficulty(DefaultLevelGenerator::DIFFICULTY difficulty);
    void execute(GameEngine &game);
};

#endif