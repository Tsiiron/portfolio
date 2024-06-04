#include <iostream>
#include "Player.h"

Player :: Player() : Player(100, 0) {}

Player :: Player(int hp, int score) : hp_(hp), score_(score) {
    between(hp, hp_max);
    between(score, score_max);
}

Player :: Player(const Player& other) : Player() {
    *this = other;
}

Player :: Player(Player&& other) : Player() {
    *this = std::move(other);
}

Player& Player :: operator= (const Player& other) {
    if(this != &other) {
        hp_ = other.hp_;
        score_ = other.score_;
    }
    return *this;
}

Player& Player :: operator= (Player&& other) {
    if(this != &other) {
        hp_ = std::move(other.hp_);
        score_ = std::move(other.score_);
    }
    return *this;
}

void Player :: between(int32_t& value, int32_t max_value) {
    value = std::min(value, max_value);
    value = std::max(value, 0);
}

int32_t Player :: get_hp() const {
    return hp_;
}

int32_t Player :: get_score() const {
    return score_;
}

void Player::set_hp(int new_value) {
    hp_ = new_value;
    between(hp_, hp_max);
}

void Player::set_score(int new_value) {
    score_ = new_value;
    between(score_, score_max);
}