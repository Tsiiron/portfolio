#ifndef game_engine_h
#define game_engine_h

#include "World/Field.h"
#include "Handlers/PlayerHandler.h"
#include "Game/State/GameState.h"
#include "FieldGenerator/DefaultLevels/DefaultLevelGenerator.h"
#include "Command/Command.h"
#include "Input/InputInterface.h"
#include "Tracking/Tracking.h"
#include "Logger/Logger.h"

class GameEngine {
private:
    GameState *state_;

    DefaultLevelGenerator::MAP_SIZE size_;
    DefaultLevelGenerator::DIFFICULTY difficulty_;
    Field *field_;
    Field *field_initial_;
    
    Player *player_;
    PlayerHandler *handler_;

    InputInterface* input_;

    Tracking* tracker_;

    Logger* logger_;
    char symb_;
    std::string command_name_;

    void clear_memory();

    GameEngine();
public:
    GameEngine(const std::string &config);
    GameEngine(InputInterface* input);
    ~GameEngine();

    void update(Command* command);

    void set_state(GameState *state);
    GameState* get_state();

    void move_player(int32_t length, PlayerHandler::Direction direction);
    void create_field();
    void main_menu();
    void exit_game();
    void start_game();
    void restart_game();
    void resize_field(DefaultLevelGenerator::MAP_SIZE new_size);
    void change_difficulty(DefaultLevelGenerator::DIFFICULTY new_difficulty);
    void add_log(int32_t value);
    void move_enemies();

    void notify(Command* command);

    void play_game();

    [[nodiscard]] PlayerHandler *handler() const;
    [[nodiscard]] Field *field() const;
};

#endif