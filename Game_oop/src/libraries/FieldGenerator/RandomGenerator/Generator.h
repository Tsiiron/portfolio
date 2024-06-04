#ifndef generator_h
#define generator_h

#include "World/Field.h"

class Generator {
private:   
    int32_t x_size_;
    int32_t y_size_;

    const int32_t event_default = 20;
    const int32_t movement_default = 20;
    const int32_t positive_default = 40;
    const int32_t negative_default = 40;

    int32_t event_;
    int32_t movement_;
    int32_t positive_;
    int32_t negative_;
    int32_t enemies_;
    
    void generate_maze(Field *field);
    void set_start_finish(Field *field);
    void generate_events(Field *field);
    void generate_enemies(Field* field, PlayerHandler* handler);

    int32_t calculate_all_passable_cells(Field *field);
    int32_t generate_int(int32_t left, int32_t right);
    void calculate_percentages(int32_t free_cells);


public:
    Generator() = delete;
    Generator(int32_t x_size, int32_t y_size, int32_t event, int32_t movement, int32_t positive, int32_t negative, int32_t enemies);
    [[nodiscard]] Field* generate(PlayerHandler* handler);
};

#endif