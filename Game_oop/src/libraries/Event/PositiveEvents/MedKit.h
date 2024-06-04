#ifndef med_kit_h
#define med_kit_h

#include "Event/Interface/EventInterface.h"
#include "Handlers/PlayerHandler.h"

class MedKit : public EventInterface {
private:
    u_int32_t heal_value;
public:
    MedKit();
    MedKit(u_int32_t value);
    void trigger(PlayerHandler* handler) const override;
    [[nodiscard]] MedKit* copy() const override;
};

#endif