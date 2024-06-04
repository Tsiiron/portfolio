#ifndef deal_damage_h
#define deal_damage_h

#include "Handlers/PlayerHandler.h"

class DealDamage {
private:
    PlayerHandler* handler_;
public:
    DealDamage() = delete;
    DealDamage(PlayerHandler* handler);

    void interaction();
};

#endif