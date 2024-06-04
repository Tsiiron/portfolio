#ifndef player_handler_h
#define player_handler_h

#include "Player/Player.h"
#include "Point/Point.h"
#include "World/Cell.h"
#include "Enemies/EnemyBase.h"

class Field;

using Coordinates = Point<int32_t>;
using Dimension = Point<int32_t>;
using Position = Point<int32_t>;

class PlayerHandler {
private:
    Player* player_ref;
    Coordinates coordinates_;
    Field* field_ref;

public:
    enum class Direction {Left, Right, Up, Down};

    PlayerHandler() = delete;
    PlayerHandler(Player* player, Field* field = nullptr);

    void set_player(Player* player);
    void set_field(Field* field);
    
    [[nodiscard]] const Coordinates& get_coordinates() const;
    [[nodiscard]] const Dimension& get_dimensions() const;
    [[nodiscard]] const Cell& get_cell(const Position& point) const;
    [[nodiscard]] int32_t get_hp() const;
    [[nodiscard]] int32_t get_score() const;
    [[nodiscard]] bool check_enemy(const Position& point) const;

    void movement(int32_t length, PlayerHandler::Direction direction);
    void set_hp(int32_t new_value);
    void set_score(int32_t new_value);
    void set_coordinates(const Coordinates& new_value);

    ~PlayerHandler();
}; 

#endif