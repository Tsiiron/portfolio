#ifndef enemy_base_h
#define enemy_base_h

#include "Point/Point.h"
using Position = Point<int32_t>;

class EnemyBase {
public:
    virtual ~EnemyBase() = default;
    
    virtual void change_coordinates() = 0;
    virtual void interact() = 0;
    [[nodiscard]] virtual const Position& get_coordinates() const = 0;
};

#endif