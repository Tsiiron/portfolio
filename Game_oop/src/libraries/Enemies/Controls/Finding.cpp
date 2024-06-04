#include "Finding.h"

Finding :: Finding(const Position& coordinates, Field* field, PlayerHandler* handler) : coordinates_(coordinates),
                                                                                        field_(field),
                                                                                        handler_(handler)
                                                                                        {}

void Finding :: move() {
    Position player_coordinates = handler_->get_coordinates();
    std::vector<Position> route = field_->find_route(coordinates_, player_coordinates);
    if(route.size() > 1) coordinates_ = route[1];
}

const Position& Finding :: get_coordinates() const {
    return coordinates_;
}