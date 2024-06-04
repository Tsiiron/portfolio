#include "Bounty.h"

Bounty :: Bounty(PlayerHandler* handler) : handler_(handler) {}

void Bounty :: interaction() {
    handler_->set_score(handler_->get_score() + (50 + rand() % 51));
}