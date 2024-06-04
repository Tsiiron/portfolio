#ifndef enemy_h
#define enemy_h

#include "World/Field.h"
#include "Handlers/PlayerHandler.h"

template<class Control, class Interaction>
class Enemy {
private:
    Control* control_;
    Interaction* interaction_;
public:
    Enemy() = delete;
    Enemy(const Position& coordinates, PlayerHandler* handler, Field* field);

    void change_coordinates();
    void interact();

    [[nodiscard]] const Position& get_coordinates() const;

    ~Enemy();
};

template<class Control, class Interaction>
Enemy<Control, Interaction> :: Enemy(const Position& coordinates, PlayerHandler* handler, Field* field) {
    control_ = new Control(coordinates, field, handler);
    interaction_ = new Interaction(handler);
}

template<class Control, class Interaction>
Enemy<Control, Interaction> :: ~Enemy() {
    if(control_) {
        delete control_;
        control_ = nullptr;
    }
    if(interaction_) {
        delete interaction_;
        interaction_ = nullptr;
    }
}

template<class Control, class Interaction>
void Enemy<Control, Interaction> :: change_coordinates() {
    control_->move();
}

template<class Control, class Interaction>
void Enemy<Control, Interaction> :: interact() {
    interaction_->interaction();
}

template<class Control, class Interaction>
const Position& Enemy<Control, Interaction> :: get_coordinates() const {
    return control_->get_coordinates();
}

#endif