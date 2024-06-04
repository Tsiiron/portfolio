#ifndef teleport_h
#define teleport_h

#include "Event/Interface/EventInterface.h"
#include "Handlers/PlayerHandler.h"
#include "Point/Point.h"

using Coordinates = Point<int32_t>;

class Teleport : public EventInterface {
private:
    Coordinates tp_coordinates;
public:
    Teleport(int32_t x, int32_t y);
    Teleport(Coordinates coords);
    void trigger(PlayerHandler* handler) const override;
    [[nodiscard]] Teleport* copy() const override;
};

#endif