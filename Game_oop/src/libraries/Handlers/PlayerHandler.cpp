#include <iostream>
#include "Player/Player.h"
#include "PlayerHandler.h"
#include "World/Field.h"

PlayerHandler :: PlayerHandler(Player* player, Field* field) : player_ref(player), field_ref(field) {
    if(player_ref == nullptr) {
        throw std::invalid_argument("В конструктор был передан nullptr - игрок");
    }
}

void PlayerHandler :: set_player(Player* player) {
    if(player != nullptr) {
        player_ref = player;
    } else throw std::invalid_argument("Был передан nullptr - игрок");
}

void PlayerHandler :: set_field(Field* field) {
    if(field != nullptr) {
        field_ref = field;
    } else throw std::invalid_argument("Был передан nullptr - поле");
}

[[nodiscard]] const Coordinates& PlayerHandler :: get_coordinates() const {
    return coordinates_;
}

[[nodiscard]] const Dimension& PlayerHandler :: get_dimensions() const {
    return field_ref->get_dimensions();
}

[[nodiscard]] const Cell& PlayerHandler :: get_cell(const Position& point) const {
    return field_ref->get_cell(point);
}


int32_t PlayerHandler :: get_hp() const {
    return player_ref->get_hp();
}

int32_t PlayerHandler :: get_score() const {
    return player_ref->get_score();
}

void PlayerHandler :: movement(int32_t length, PlayerHandler::Direction direction) {

    if(field_ref == nullptr) throw std::invalid_argument("Не было инициализировано поле");

    for(int32_t i = 0; i < length; i++) {
        Coordinates new_pos;
        switch(direction)
        {
            case Direction::Left:
                new_pos = coordinates_ + Coordinates{-1, 0};
                break;
            case Direction::Right:
                new_pos = coordinates_ + Coordinates{1, 0};
                break;
            case Direction::Up:
                new_pos = coordinates_ + Coordinates{0, -1};
                break;
            case Direction::Down:
                new_pos = coordinates_ + Coordinates{0, 1};
                break;
        }
        
        set_coordinates(new_pos);
        
    }
    
}

void PlayerHandler :: set_hp(int32_t new_value) {
    player_ref->set_hp(new_value);
}

void PlayerHandler :: set_score(int32_t new_value) {
    player_ref->set_score(new_value);
}

void PlayerHandler :: set_coordinates(const Coordinates& new_value) {
    if(field_ref == nullptr) throw std::invalid_argument("Не было инициализировано поле");

    if(field_ref->get_cell(new_value).is_passable()) {
        coordinates_ = new_value;
        auto active_event = field_ref->get_cell(coordinates_).get_event();
        if(active_event != nullptr) {
            active_event->trigger(this);
        }
    // }
    } else throw std::invalid_argument("Клетка поля непроходима");
}

bool PlayerHandler :: check_enemy(const Position& point) const {
    for(auto& enemy : field_ref->get_enemies()) {
        if(enemy->get_coordinates() == point) return true;
    }
    return false;
}

PlayerHandler :: ~PlayerHandler() {
    if(player_ref != nullptr) {
        delete player_ref;
        player_ref = nullptr;
    }
    if(field_ref  != nullptr) {
        delete field_ref;
        field_ref = nullptr;
    }
}