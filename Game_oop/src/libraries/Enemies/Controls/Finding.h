#ifndef finding_h
#define finding_h

#include "World/Field.h"
#include "Handlers/PlayerHandler.h"

class Finding {
private:
    Position coordinates_;
    Field* field_;
    PlayerHandler* handler_;
public:
    Finding() = delete;
    Finding(const Position& coordinates, Field* field, PlayerHandler* handler);

    void move();
    [[nodiscard]] const Position& get_coordinates() const;

};

#endif