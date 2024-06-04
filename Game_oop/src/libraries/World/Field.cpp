#include "Field.h"
#include <iostream>
#include <queue>
#include <vector>
#include <map>

void Field :: clear_field() {
    if(field_ == nullptr) return;

    for(int i = 0; i < dimensions_.get_y(); i++) {
        delete[] field_[i];
    }
    delete[] field_;
    field_ = nullptr;
}

Cell** Field :: create_field(const Position& dimensions) {
    Cell** arr = new Cell* [dimensions.get_y()];
    
    for(int i = 0; i < dimensions.get_y(); i++) {
        arr[i] = new Cell[dimensions.get_x()];
    }
    return arr;
}

Field :: Field(const Position& dimensions) : dimensions_(dimensions), start_({-1, -1}), finish_({-1, -1}), field_(nullptr) {
    if(dimensions_.get_x() < MAP_SIZE_LOWER_BOUND || dimensions_.get_y() < MAP_SIZE_LOWER_BOUND 
        || dimensions.get_x() > MAP_SIZE_UPPER_BOUND || dimensions.get_y() > MAP_SIZE_UPPER_BOUND) {
        throw std::invalid_argument("Неверные значения размера карты");
    }
    field_ = create_field(dimensions_);
}

Field :: Field(int32_t x_size, int32_t y_size) : Field(Point{x_size, y_size}) {}

Field :: Field() : Field(MAP_SIZE_LOWER_BOUND, MAP_SIZE_LOWER_BOUND) {}

Field :: Field(const Field& other) : Field() {
    *this = other;
}

Field :: Field(Field&& other) : Field() {
    *this = std::move(other);
}

Field& Field :: operator= (const Field& other) {
    if(&other != this) {
        clear_field();
        field_ = create_field(other.dimensions_);

        dimensions_ = other.dimensions_;
        start_ = other.start_;
        finish_ = other.finish_;
        enemies_ = other.enemies_;

        for(int i = 0; i < dimensions_.get_y(); i++) {
            for(int j = 0; j < dimensions_.get_x(); j++) {
                field_[i][j] = other.field_[i][j];
            }
        }
    }
    return *this;
}

Field& Field :: operator= (Field&& other) {
    if(&other != this) {
        clear_field();
        dimensions_ = std::move(other.dimensions_);
        start_ = std::move(other.start_);
        finish_ = std::move(other.finish_);
        field_ = std::move(other.field_);
        enemies_ = std::move(other.enemies_);

        other.field_ = nullptr;
    }
    return *this;
}

bool Field :: is_on_map(const Position& point) const {
    return point.get_x() >= 0 && point.get_y() >= 0 && point.get_x() < dimensions_.get_x() && point.get_y() < dimensions_.get_y();
}

bool Field :: can_move(const Position& point) const {
    return is_on_map(point) && get_cell(point).is_passable();
}

[[nodiscard]] const Position& Field :: get_start_point() const{
    return start_;
}

[[nodiscard]] const Position& Field :: get_finish_point() const{
    return finish_;
}

[[nodiscard]] const Dimension& Field :: get_dimensions() const {
    return dimensions_;
}

Cell& Field :: get_cell(const Position& point) const {
    if(!is_on_map(point)) {
        throw std::out_of_range("Точка находится вне карты");
    }
    return field_[point.get_y()][point.get_x()];
}

[[nodiscard]] std::vector<Position> Field :: get_possible_moves() const {
    return {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
}

void Field :: set_start(const Position& point) {
    if(can_move(point)) {
        if(start_ != Position{-1, -1}) {
            field_[start_.get_y()][start_.get_x()].set_type(Cell::Type::PASSABLE);
        }
        start_ = point;
        field_[start_.get_y()][start_.get_x()].set_type(Cell::Type::ENTRANCE);
    }
}

void Field :: set_finish(const Position& point) {
    if(can_move(point)) {
        if(finish_ != Position{-1, -1}) {
            field_[finish_.get_y()][finish_.get_x()].set_type(Cell::Type::PASSABLE);
        }
        finish_ = point;
        field_[finish_.get_y()][finish_.get_x()].set_type(Cell::Type::EXIT);
    }
}

void Field :: create_wall(const Position& point) {
    if(is_on_map(point) && get_cell(point).is_passable()) {
        field_[point.get_y()][point.get_x()].set_type(Cell::Type::WALL);
    }
}

void Field :: make_passable(const Position& point) {
    if(is_on_map(point) && !get_cell(point).is_passable()) {
        field_[point.get_y()][point.get_x()].set_type(Cell::Type::PASSABLE);
    }
}

void Field :: set_cell(const Position& point, const Cell& new_cell) {
    if(!is_on_map(point)) return;
    field_[point.get_y()][point.get_x()] = new_cell;
}

void Field :: set_cell(const Position& point, Cell&& new_cell) {
    if(!is_on_map(point)) return;
    field_[point.get_y()][point.get_x()] = std::move(new_cell);
}

std::ostream &Field :: print(std::ostream &out) const{
	for (int32_t y = 0; y < dimensions_.get_y(); y++)
	{
		for (int32_t x = 0; x < dimensions_.get_x(); x++)
		{
			out << get_cell(Position{x, y});
			out << std::flush;
		}
		out << std::endl;
	}
	return out << std::endl;
}

[[nodiscard]] std::vector<Position> Field :: find_route(const Position &start, const Position &finish) const {
    auto heuristic = [](const Position &pos1, const Position &pos2) {
        return abs(pos1.get_x() - pos2.get_x()) + abs(pos1.get_y() - pos2.get_y());
    };

    std::priority_queue<std::pair<int, Position>, std::vector<std::pair<int, Position>>, std::greater<>> frontier;
    std::map<Position, Position> came_from;
    std::map<Position, int32_t> cost_so_far;
    bool found_path = false;

    frontier.push(std::make_pair(0, start));
    cost_so_far[start] = 0;

    while(!frontier.empty()) {
        Position current = frontier.top().second;
        frontier.pop();

        if(current == finish) {
            found_path = true;
            break;
        }

        for(auto &dir : get_possible_moves()) {
            const Position &next = current + dir;

            if(!can_move(next)) {
                continue;
            }

            int32_t new_cost = cost_so_far[current] + 1;

            if(cost_so_far.find(next) == cost_so_far.end() || new_cost < cost_so_far[next]) {
                cost_so_far[next] = new_cost;
                int32_t priority = new_cost + heuristic(next, finish);
                frontier.push(std::make_pair(priority, next));
                came_from[next] = current;
            }
        }
    }

    std::vector<Position> path;

    if(found_path) {
        Position current = finish;
        while(current != start) {
            path.push_back(current);
            current = came_from[current];
        }
        path.push_back(start);
        std::reverse(path.begin(), path.end());
    }

    return path;
}


Field :: ~Field() {
    clear_field();
}

