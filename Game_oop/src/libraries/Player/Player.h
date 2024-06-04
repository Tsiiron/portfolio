#ifndef player_h
#define player_h
#include <iostream>

class Player{
private:

    const int32_t hp_max = 100;
    const int32_t score_max = 1000;

    int32_t hp_;
    int32_t score_;

    void between(int32_t &value, int32_t max_value);
    
public:

    Player();
    Player(int32_t hp, int32_t score);
    Player(const Player& other);
    Player(Player&& other);

    Player& operator= (const Player& other);
    Player& operator= (Player&& other);

    int32_t get_hp() const;
    int32_t get_score() const;

    void set_hp(int32_t new_value);
    void set_score(int32_t new_value);

};


#endif 