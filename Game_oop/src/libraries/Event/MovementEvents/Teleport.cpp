#include "Teleport.h"

Teleport :: Teleport(Coordinates coords) : tp_coordinates(coords) {}

Teleport :: Teleport(int32_t x, int32_t y) : Teleport(Coordinates{x,y}) {}

void Teleport :: trigger(PlayerHandler* handler) const {
    handler->set_coordinates(tp_coordinates);
}

[[nodiscard]] Teleport* Teleport :: copy() const {
    return new Teleport(*this);
}