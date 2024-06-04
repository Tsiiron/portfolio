#include "Wandering.h"

Wandering :: Wandering(const Position& coordinates, Field* field, PlayerHandler* handler) : coordinates_(coordinates),
                                                                                            field_(field)
                                                                                            {}                                                               

const Position& Wandering :: get_coordinates() const {
    return coordinates_;
}

std::vector<Position> Wandering :: possible_coordinates() const {
    std::vector<Position> possible_moves = field_->get_possible_moves();
    std::vector<Position> elligble_coordinates;
    for(auto move : possible_moves) {
        Position new_coordinates = move + coordinates_;
        if(field_->can_move(new_coordinates)) {
            elligble_coordinates.push_back(new_coordinates);
        }
    }
    return elligble_coordinates;
}

void Wandering :: move() {
    std::vector<Position> elligble_coordinates = possible_coordinates();
    auto it = elligble_coordinates.begin();
    int random = rand() % elligble_coordinates.size();
    std::advance(it, random);
    coordinates_ = *it;
}