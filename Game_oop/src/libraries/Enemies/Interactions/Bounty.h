#ifndef bounty_h
#define bounty_h

#include "Handlers/PlayerHandler.h"

class Bounty {
private:
    PlayerHandler* handler_;
public:
    Bounty() = delete;
    Bounty(PlayerHandler* handler);

    void interaction();
};

#endif