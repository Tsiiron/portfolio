#ifndef field_h
#define field_h

#include "Cell.h"
#include "Point/Point.h"
#include "Enemies/EnemyBase.h"
#include "Enemies/EnemyDerived.h"
#include <cstdint>
#include <memory>

using Position = Point<int32_t>;
using Dimension = Point<int32_t>;

#define MAP_SIZE_UPPER_BOUND 500
#define MAP_SIZE_LOWER_BOUND 10

class Field {
private:
    
    Cell** field_;
    Dimension dimensions_;
    Position start_, finish_;
    std::vector<EnemyBase*> enemies_;
    
    void clear_field();
    Cell** create_field(const Dimension& dimensions);
    
public:

    Field();
    Field(int32_t x_size, int32_t y_size);
    Field(const Dimension& dimensions);

    Field(const Field& other);
    Field(Field&& other);

    Field& operator= (const Field& other);
    Field& operator= (Field&& other);

    void set_start(const Position& point);
    void set_finish(const Position& point);
    void create_wall(const Position& point);
    void make_passable(const Position& point);

    void set_cell(const Position& point, const Cell& new_cell);
    void set_cell(const Position& point, Cell&& new_cell);  

    [[nodiscard]] const Position& get_start_point() const;
    [[nodiscard]] const Position& get_finish_point() const;
    [[nodiscard]] const Dimension& get_dimensions() const;
    [[nodiscard]] Cell& get_cell(const Position& point) const;
    [[nodiscard]] std::vector<Position> get_possible_moves() const;
    
    [[nodiscard]] std::vector<Position> find_route(const Position &start, const Position &finish) const;

    bool is_on_map(const Position& point) const;
    bool can_move(const Position& point) const;

    std::ostream &print(std::ostream &out) const;

    template<class Control, class Interaction>
    void add_enemy(const Position& coordinates, PlayerHandler* handler, Field* field) {
        auto enemy = new EnemyDerived<Control, Interaction>(coordinates, handler, field);
        enemies_.push_back(enemy);
    }
    
    [[nodiscard]] const std::vector<EnemyBase*>& get_enemies() const {
        return enemies_;
    }

    void delete_enemy(EnemyBase* enemy) {
        auto it = std::find(enemies_.begin(), enemies_.end(), enemy);
        if(it != enemies_.end()) {
            enemies_.erase(it);
        }
    }

    ~Field();
};

#endif