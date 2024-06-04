#include "StreamInput.h"
#include "Defines.h"
#include <iostream>
#include <sstream>
#include <termios.h>
#include <cstdio>
#include <unistd.h>

StreamInput :: StreamInput(const std::string &config, std::istream &in) : last_command_(nullptr), iistream_(in) {
    std::ifstream file(config);

    if(!file.is_open()) {
        clean_up();
        throw std::invalid_argument("Не удалось открыть файл: " + config);
    }

    initializate_available_commands();
    parse_commands(file);
}

StreamInput :: ~StreamInput() {
    clean_up();
}

void StreamInput :: clean_up() {
    user_binds.clear();
    for(auto &[key, value] : available_commands_) {
        delete value.second;
        value.second = nullptr;
    }
    available_commands_.clear();
}

void StreamInput :: initializate_available_commands() {
    // movement
    available_commands_["left"] = {false, new MovePlayer(PlayerHandler::Direction::Left)};
    available_commands_["right"] = {false, new MovePlayer(PlayerHandler::Direction::Right)};
    available_commands_["up"] = {false, new MovePlayer(PlayerHandler::Direction::Up)};
    available_commands_["down"] = {false, new MovePlayer(PlayerHandler::Direction::Down)};

    // game states
    available_commands_["start"] = {false, new StartGame};
    available_commands_["restart"] = {false, new RestartGame};
    available_commands_["exit"] = {false, new ExitGame};
    available_commands_["menu"] = {false, new GoMainMenu};

    // field settings
    available_commands_["size_small"] = {false, new ChangeFieldSize(DefaultLevelGenerator::MAP_SIZE::SMALL)};
    available_commands_["size_medium"] = {false, new ChangeFieldSize(DefaultLevelGenerator::MAP_SIZE::MEDIUM)};
    available_commands_["size_huge"] = {false, new ChangeFieldSize(DefaultLevelGenerator::MAP_SIZE::HUGE)};
    available_commands_["difficulty_easy"] = {false, new ChangeDifficulty(DefaultLevelGenerator::DIFFICULTY::EASY)};
    available_commands_["difficulty_hard"] = {false, new ChangeDifficulty(DefaultLevelGenerator::DIFFICULTY::HARD)};   

    // logging
    available_commands_["log_cout"] = {false, new LoggingStream};
    available_commands_["log_file"] = {false, new LoggingFile};
}

void StreamInput :: parse_commands(std::ifstream &stream) {
    std::string line;

    while(std::getline(stream, line)) {
        parse_command(line);
    }

    if(user_binds.size() < 15) {
        clean_up();
        throw std::invalid_argument("Недостаточно ключей для инициализации");
    }
}

void StreamInput :: parse_command(const std::string &command) {
    std::istringstream iss(command);
    std::string cmd;
    int32_t key;

    iss >> cmd >> key;

    if(available_commands_.find(cmd) == available_commands_.end()) {
        clean_up();
        throw std::invalid_argument("Была подана команда которой не существует: " + cmd);
    }
    if(available_commands_[cmd].first) {
        clean_up();
        throw std::invalid_argument("Данная команда была проинициализирована ранее: " + cmd);
    }
    if(user_binds.find(key) != user_binds.end()) {
        clean_up();
        throw std::invalid_argument("Данная кнопка уже была проинициализирована раннее: " + std::to_string(static_cast<char>(key)));
    }

    user_binds[key] = cmd;
}

Command* StreamInput :: get_command() {
    return last_command_;
}

void StreamInput :: update() {
    last_command_ = nullptr;
    char command;

    termios saved_attribute;
    tcgetattr(STDIN_FILENO, &saved_attribute);

    termios unbuf_attribute = saved_attribute;
    unbuf_attribute.c_lflag &= ~ICANON;

    tcsetattr(STDIN_FILENO, TCSANOW, &unbuf_attribute);
    command = iistream_.get();
    tcsetattr(STDIN_FILENO, TCSANOW, &saved_attribute);

    symb_ = command;

    int32_t key = static_cast<int32_t>(command);
    if(user_binds.find(key) != user_binds.end()) {
        command_name_ = user_binds.at(key);
        last_command_ = available_commands_.at(command_name_).second;
    } else {
        command_name_ = "";
    }
}

char StreamInput :: get_symb() {
    return symb_;
}

std::string StreamInput :: get_name() {
    return command_name_;
}
