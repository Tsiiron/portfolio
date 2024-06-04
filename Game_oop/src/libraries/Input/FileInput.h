#ifndef file_input_h
#define file_input_h

#include "InputInterface.h"
#include "Command/Command.h"
#include <istream>
#include <cstdio>
#include <fstream>
#include <string>
#include <unordered_map>

class FileInput : public InputInterface{
private:
    Command* last_command_;
    std::ifstream file_;

    std::unordered_map<std::string, std::pair<bool, Command*>> available_commands_;
    std::unordered_map<int32_t, std::string> user_binds;

    char symb_;
    std::string command_name_;

    void clean_up();
    void initializate_available_commands();
    void parse_commands(std::ifstream &stream);
    void parse_command(const std::string &command);
    void open_file(const std::string &file_name);
public:
    FileInput(const std::string &config, const std::string &file_name);

    Command* get_command() override;
    void update() override;
    char get_symb() override;
    std::string get_name() override;

    ~FileInput() override;
};

#endif