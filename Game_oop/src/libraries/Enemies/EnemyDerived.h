#ifndef enemy_derived_h
#define enemy_derived_h

#include "World/Field.h"
#include "Handlers/PlayerHandler.h"
#include "Enemies/EnemyBase.h"
#include "Enemies/Enemy.h"

template<class Control, class Interaction>
class EnemyDerived : public EnemyBase {
private:
    Enemy<Control, Interaction> enemy_;

public:
    EnemyDerived(const Position& coordinates, PlayerHandler* handler, Field* field) : enemy_(coordinates, handler, field) {}

    void change_coordinates() override {
        enemy_.change_coordinates();
    }

    void interact() override {
        enemy_.interact();
    }

    [[nodiscard]] const Position& get_coordinates() const override {
        return enemy_.get_coordinates();
    }
};

#endif