#include "GameEngine.h"
#include "../State/LoseState.h"
#include "../State/WinState.h"
#include "../State/MainMenuState.h"
#include "../State/PlayingState.h"
#include "../State/EndState.h"
#include "Command/MovePlayer.h"
#include "Input/StreamInput.h"
#include "Messages/Defines.h"

GameEngine :: GameEngine() : state_(new MainMenuState),
                            size_(DefaultLevelGenerator::MAP_SIZE::SMALL),
                            difficulty_(DefaultLevelGenerator::DIFFICULTY::EASY),
                            field_(nullptr),
                            field_initial_(nullptr),
                            player_(nullptr),
                            handler_(nullptr),
                            tracker_(new Tracking(nullptr, std::cout)),
                            logger_(nullptr)
{
    logger_ = new Logger;
}

GameEngine :: GameEngine(const std::string &config) : GameEngine() {
    input_ = new StreamInput(config, std::cin);
}

GameEngine :: GameEngine(InputInterface* input) : GameEngine() {
    input_ = input;
}

GameEngine :: ~GameEngine() {
    clear_memory();
    delete state_;
    state_ = nullptr;
    if(logger_) {
        delete logger_;
        logger_ = nullptr;
    }
    if(tracker_) {
        delete tracker_;
        tracker_ = nullptr;
    }
}

void GameEngine :: clear_memory() {
    if(handler_) {
        delete handler_;
        handler_ = nullptr;
    }
    field_ = nullptr;
    player_ = nullptr;
}

void GameEngine :: move_enemies() {
    for(auto& enemy : field_->get_enemies()) {
        enemy->change_coordinates();
        if(enemy->get_coordinates() == handler_->get_coordinates()) {
            enemy->interact();
            field_->delete_enemy(enemy);
        }
    }
}

void GameEngine :: update(Command* command) {
    if(command == nullptr) {
        logger_->set_log(new WrongCommandMessage(symb_));
        return;
    }

    bool result = state_->execute_command(*this, command);

    if(result) {
        if(typeid(*command) == typeid(MovePlayer)) {
            move_enemies();
        }
        notify(command);
        logger_->set_log(new CorrectCommandMessage(symb_, command_name_));
        // std::cerr << "Выполнено\n";
    } else {
        logger_->set_log(new WrongCommandMessage(symb_));
        // std::cerr << "Не выполнено\n";
    }
}

void GameEngine :: set_state(GameState *state) {
    delete state_;
    state_ = state;

    if(typeid(*state_) == typeid(WinState)) {
        logger_->set_log(new WinMessage(*this));
    }

    if(typeid(*state_) == typeid(LoseState)) {
        logger_->set_log(new LoseMessage(*this));
    }

    if(typeid(*state_) == typeid(WinState) || typeid(*state_) == typeid(LoseState)) {
        tracker_->update(state_);
    }
}

GameState* GameEngine :: get_state() {
    return state_;
}

void GameEngine :: move_player(int32_t length, PlayerHandler::Direction direction) {
    if(handler_ == nullptr) return;
    try {
        handler_->movement(length, direction);
    } catch (std::invalid_argument const& err) {
        std::cerr << err.what() << '\n';
    }
    
}

void GameEngine :: exit_game() {
    clear_memory();
    set_state(new EndState);
}

void GameEngine :: main_menu() {
    set_state(new MainMenuState);
}

void GameEngine :: create_field() {
    if(field_initial_ != nullptr) {
        delete field_initial_;
        field_initial_ = nullptr;
    }
    player_ = new Player;
    handler_ = new PlayerHandler(player_);
    DefaultLevelGenerator generator(size_, difficulty_);
    field_initial_ = generator.generate(handler_);
}

void GameEngine :: start_game() {
    create_field();
    restart_game();
}

void GameEngine :: restart_game() {
    // if(handler_ != nullptr) delete handler_;
    if(field_initial_ == nullptr) {
        start_game();
    }
    field_ = nullptr;
    field_ = new Field(*field_initial_);
    handler_->set_field(field_);
    handler_->set_hp(100);
    handler_->set_score(0);
    tracker_ = new Tracking(handler_, std::cout);
    handler_->set_coordinates(field_->get_start_point());
    logger_->set_log(new NewGameMessage(*this));

    set_state(new PlayingState);
}

void GameEngine :: resize_field(DefaultLevelGenerator::MAP_SIZE new_size) {
    size_ = new_size;
}

void GameEngine :: change_difficulty(DefaultLevelGenerator::DIFFICULTY new_difficulty) {
    difficulty_ = new_difficulty;
}

PlayerHandler* GameEngine :: handler() const {
    return handler_;
}

Field* GameEngine :: field() const {
    return field_;
}

void GameEngine :: notify(Command* command) {
    tracker_->update(command);
}

void GameEngine :: add_log(int32_t value) {
    logger_ -> add_logger(value);
}

void GameEngine :: play_game() {
    do {
        input_->update();
        symb_ = input_->get_symb();
        command_name_ = input_->get_name();
        update(input_->get_command());
    } while (dynamic_cast<EndState*>(get_state()) == nullptr);
    
}