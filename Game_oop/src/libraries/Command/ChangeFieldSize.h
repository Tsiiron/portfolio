#ifndef change_field_size_h
#define change_field_size_h

#include "Command/Command.h"
#include "Game/Engine/GameEngine.h"
#include "FieldGenerator/DefaultLevels/DefaultLevelGenerator.h"

class ChangeFieldSize : public Command {
private:
    DefaultLevelGenerator::MAP_SIZE size_;
public:
    ChangeFieldSize();
    ChangeFieldSize(DefaultLevelGenerator::MAP_SIZE size);
    void execute(GameEngine &game);
};

#endif