#include "DealDamage.h"

DealDamage :: DealDamage(PlayerHandler* handler) : handler_(handler) {}

void DealDamage :: interaction() {
    handler_->set_hp(handler_->get_hp() - (25 + rand() % 26));
}