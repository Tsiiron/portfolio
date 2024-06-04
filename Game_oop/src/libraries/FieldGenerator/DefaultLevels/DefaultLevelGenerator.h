#ifndef default_level_generator_h
#define default_level_generator_h

#include "World/Field.h"
#include "FieldGenerator/RandomGenerator/Generator.h"

class DefaultLevelGenerator {
public:
    enum class MAP_SIZE {SMALL, MEDIUM, HUGE};
    enum class DIFFICULTY {EASY, HARD};
private:
    MAP_SIZE size_;
    DIFFICULTY difficulty_;
public:
    DefaultLevelGenerator() = delete;
    DefaultLevelGenerator(MAP_SIZE size, DIFFICULTY difficulty);
    [[nodiscard]] Field* generate(PlayerHandler* handler) const;
};

#endif