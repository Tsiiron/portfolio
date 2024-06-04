#include "Trap.h"

Trap :: Trap(u_int32_t value) : damage_value(value) {}

Trap :: Trap() : Trap(30) {}

void Trap :: trigger(PlayerHandler* handler) const {
    handler->set_hp(handler->get_hp() - damage_value);
}

[[nodiscard]] Trap* Trap :: copy() const {
    return new Trap(*this);
}