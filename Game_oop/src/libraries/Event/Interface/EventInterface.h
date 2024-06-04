#ifndef event_interface_h
#define event_interface_h

class PlayerHandler;

class EventInterface {
public:         
    virtual void trigger(PlayerHandler* handler) const = 0;
    [[nodiscard]] virtual EventInterface* copy() const = 0;
};

#endif