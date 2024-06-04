#ifndef trap_h
#define trap_h

#include "Event/Interface/EventInterface.h"
#include "Handlers/PlayerHandler.h"

class Trap : public EventInterface {
private:
    u_int32_t damage_value;
public:
    Trap();
    Trap(u_int32_t value);
    void trigger(PlayerHandler* handler) const override;
    [[nodiscard]] Trap* copy() const override;
};

#endif