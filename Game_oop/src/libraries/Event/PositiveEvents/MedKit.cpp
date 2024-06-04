#include "MedKit.h"

MedKit :: MedKit(u_int32_t value) : heal_value(value) {}

MedKit :: MedKit() : MedKit(25) {}

void MedKit :: trigger(PlayerHandler* handler) const {
    handler->set_hp(handler->get_hp() + heal_value);
}

[[nodiscard]] MedKit* MedKit :: copy() const {
    return new MedKit(*this);
}