#include "Generator.h"
#include <random>
#include <vector>
#include <iostream>
#include "Event/MovementEvents/Teleport.h"
#include "Event/NegativeEvents/Trap.h"
#include "Event/PositiveEvents/MedKit.h"
#include "Enemies/EnemyDefines.h"

Generator :: Generator(int32_t x_size, int32_t y_size, int32_t event, 
                       int32_t movement, int32_t positive, int32_t negative,
                       int32_t enemies) :
                       x_size_(x_size), 
                       y_size_(y_size),
                       event_(event), 
                       movement_(movement), 
                       positive_(positive), 
                       negative_(negative),
                       enemies_(enemies)
                       {}

int32_t Generator :: generate_int(int32_t left, int32_t right) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int32_t> distribution(left, right - 1);

	return distribution(gen);
}

void Generator :: generate_maze(Field *field) {
    enum class Direction{LEFT, RIGHT, UP, DOWN};

    if(field == nullptr) return;

    for(int32_t i = 0; i < field->get_dimensions().get_y(); i++) {
        for(int32_t j = 0; j < field->get_dimensions().get_x(); j++) {
            field->create_wall({j,i});
        }
    }

    int32_t x = generate_int(0, field->get_dimensions().get_x());
    int32_t y = generate_int(0, field->get_dimensions().get_y());
    field->make_passable({x,y});

    std::vector<Position> to_check;
    if(y - 2 >= 0) {
        to_check.push_back(Position{x, y - 2});
    }
    if(y + 2 < field->get_dimensions().get_y()) {
        to_check.push_back(Position{x, y + 2});
    }
    if(x - 2 >= 0) {
        to_check.push_back(Position{x - 2, y});
    }
    if(x + 2 < field->get_dimensions().get_x()) {
        to_check.push_back(Position{x + 2, y});
    }

    while(to_check.size() > 0) {
        int32_t index = generate_int(0, to_check.size());
        Position cell = to_check[index];
        x = cell.get_x();
        y = cell.get_y();
        field->make_passable({x,y});
        to_check.erase(to_check.begin() + index);

        std::vector<Direction> d = {Direction::LEFT, Direction::RIGHT, Direction::UP, Direction::DOWN};

        while(d.size() > 0) {
            bool t = true;
            int32_t dir_index = generate_int(0, d.size());
            switch(d[dir_index]) {
                case Direction::DOWN:
                    if(y + 2 < field->get_dimensions().get_y() && field->get_cell({x, y + 2}).is_passable()) {
                        field->make_passable({x, y + 1});
                        d = {};
                        t = false;
                    }
                    break;
                case Direction::UP:
                    if(y - 2 >= 0 && field->get_cell({x, y - 2}).is_passable()) {
                        field->make_passable({x, y - 1});
                        d = {};
                        t = false;
                    }
                    break;
                case Direction::LEFT:
                    if(x - 2 >= 0 && field->get_cell({x - 2, y}).is_passable()) {
                        field->make_passable({x - 1, y});
                        d = {};
                        t = false;
                    }
                    break;
                case Direction::RIGHT:
                    if(x + 2 < field->get_dimensions().get_x() && field->get_cell({x + 2, y}).is_passable()) {
                        field->make_passable({x + 1, y});
                        d = {};
                        t = false;
                    }
                    break;
            }

            if(t) d.erase(d.begin() + dir_index);
        }

        if(y - 2 >= 0 && field->get_cell({x, y - 2}).is_wall()) {
            to_check.push_back({x, y - 2});
        }
        if(y + 2 < field->get_dimensions().get_y() && field->get_cell({x, y + 2}).is_wall()) {
            to_check.push_back({x, y + 2});
        }
        if(x - 2 >= 0 && field->get_cell({x - 2, y}).is_wall()) {
            to_check.push_back({x - 2, y});
        }
        if(x + 2 < field->get_dimensions().get_x() && field->get_cell({x + 2, y}).is_wall()) {
            to_check.push_back({x + 2, y});
        } 
    }

    Dimension dim = field->get_dimensions();

    for(int32_t i = 0; i < dim.get_x(); i++) {
        field->create_wall({i, 0});
        field->create_wall({i, dim.get_y() - 1});
    }

    for(int32_t i = 0; i < dim.get_y(); i++) {
        field->create_wall({0, i});
        field->create_wall({dim.get_x() - 1, i});
    }
}

void Generator :: set_start_finish(Field *field) {
    Dimension dim = field->get_dimensions();
    bool start_top = generate_int(0, 2) == 0 ? true : false;
    Position start, finish;

    if(start_top) {
        do start = {0, generate_int(0, dim.get_y() / 2 + 1)};
        while(field->get_cell(start + Position{1, 0}).is_wall());

        do finish = {dim.get_x() - 1, generate_int(dim.get_y() / 2, dim.get_y())};
        while(field->get_cell(finish + Position{-1, 0}).is_wall());
    } else {
        do start = {0, generate_int(dim.get_y() / 2, dim.get_y())};
        while(field->get_cell(start + Position{1, 0}).is_wall());

        do finish = {dim.get_x() - 1, generate_int(0, dim.get_y() / 2 + 1)};
        while(field->get_cell(finish + Position{-1, 0}).is_wall());
    }

    field->get_cell(start).set_type(Cell::Type::ENTRANCE);
    field->get_cell(finish).set_type(Cell::Type::EXIT);

    field->set_start(start);
    field->set_finish(finish);
}

int32_t Generator :: calculate_all_passable_cells(Field *field) {
    int32_t cnt = 0;
    for(int32_t y = 0; y < y_size_; y++) {
        for(int32_t x = 0; x < x_size_; x++) {
            if(field->get_cell({x, y}).is_passable()) cnt++;
        }
    }
    return cnt;
}

void Generator :: calculate_percentages(int32_t free_cells) {

    if(event_ < 0 || event_ > 100) event_ = event_default;
    if(movement_ + positive_ + negative_ > 100) {
        movement_ = movement_default;
        positive_ = positive_default;
        negative_ = negative_default;
    }

    event_ = static_cast<int32_t>(free_cells * 1.0 * event_ / 100.0);
    movement_ = static_cast<int32_t>(event_ * 1.0 * movement_ / 100.0);
    positive_ = static_cast<int32_t>(event_ * 1.0 * positive_ / 100.0);
    negative_ = static_cast<int32_t>(event_ * 1.0 * negative_ / 100.0);

}

void Generator :: generate_events(Field *field) {
    calculate_percentages(calculate_all_passable_cells(field));

    int32_t movement_cnt = 0;
    int32_t positive_cnt = 0;
    int32_t negative_cnt = 0;

    Position point, new_point;
    Dimension dim = field->get_dimensions();

    while(movement_cnt != movement_) {
        point = {generate_int(1, dim.get_x() - 1), generate_int(1, dim.get_y() - 1)};
        if(field->get_cell(point).is_passable() && field->get_cell(point).get_event() == nullptr) {
            new_point = {-1, -1};
            while(!field->can_move(new_point)) {
                new_point = {generate_int(point.get_x() - 5, point.get_x() + 6), generate_int(point.get_y() - 5, point.get_y() + 6)};
            }
            field->get_cell(point).add_event(new Teleport(new_point));
            movement_cnt++;
        }
    }

    while(positive_cnt != positive_) {
        point = {generate_int(1, dim.get_x() - 1), generate_int(1, dim.get_y() - 1)};
        if(field->get_cell(point).is_passable() && field->get_cell(point).get_event() == nullptr) {
            field->get_cell(point).add_event(new MedKit(generate_int(10, 26)));
            positive_cnt++;
        }
    }

    while(negative_cnt != negative_) {
        point = {generate_int(1, dim.get_x() - 1), generate_int(1, dim.get_y() - 1)};
        if(field->get_cell(point).is_passable() && field->get_cell(point).get_event() == nullptr) {
            field->get_cell(point).add_event(new Trap(generate_int(20, 41)));
            negative_cnt++;
        }
    }

    std::vector<Position> route = field->find_route(field->get_start_point(), field->get_finish_point());

    for(auto point : route) {
        if(field->get_cell(point).get_event() != nullptr) {
            auto acitve_event = field->get_cell(point).get_event();
            if(const auto *ptr = dynamic_cast<const Teleport*>(acitve_event); ptr != nullptr) field->get_cell(point).remove_event();
        }
    }
}

void Generator :: generate_enemies(Field* field, PlayerHandler* handler) {
    Dimension dim = field->get_dimensions();
    Position point;
    for(size_t i = 0; i < enemies_; i++) {
        int32_t control = generate_int(0, 2);
        int32_t interaction = generate_int(0, 2);
        do {
            point = {generate_int(1, dim.get_x() - 1), generate_int(1, dim.get_y() - 1)};
        } while(!field->can_move(point));
        
        if(control == 0 && interaction == 0) {
            field->add_enemy<Finding, Bounty>(point, handler, field);
        } else if(control == 0 && interaction == 1) {
            field->add_enemy<Finding, DealDamage>(point, handler, field);
        } else if(control == 1 && interaction == 0) {
            field->add_enemy<Wandering, Bounty>(point, handler, field);
        } else {
            field->add_enemy<Wandering, DealDamage>(point, handler, field);
        }
    }
}

[[nodiscard]] Field* Generator :: generate(PlayerHandler* handler) {
    auto *field = new Field(x_size_, y_size_);
    generate_maze(field);
    set_start_finish(field);
    generate_events(field);
    generate_enemies(field, handler);
    return field;
}