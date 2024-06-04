#ifndef wandering_h
#define wandering_h

#include "World/Field.h"
#include "Handlers/PlayerHandler.h"

class Wandering {
private:
    Position coordinates_;
    Field* field_;

    std::vector<Position> possible_coordinates() const;
public:
    Wandering() = delete;
    Wandering(const Position& coordinates, Field* field, PlayerHandler* handler);

    void move();
    [[nodiscard]] const Position& get_coordinates() const;

};

#endif