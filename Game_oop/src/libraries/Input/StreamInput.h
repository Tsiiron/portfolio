#ifndef stream_input_h
#define stream_input_h

#include "InputInterface.h"
#include "Command/Command.h"
#include <istream>
#include <cstdio>
#include <fstream>
#include <string>
#include <unordered_map>

class StreamInput : public InputInterface{
private:
    Command* last_command_;
    std::istream& iistream_;

    std::unordered_map<std::string, std::pair<bool, Command*>> available_commands_;
    std::unordered_map<int32_t, std::string> user_binds;

    char symb_;
    std::string command_name_;

    void clean_up();
    void initializate_available_commands();
    void parse_commands(std::ifstream &stream);
    void parse_command(const std::string &command);
public:
    StreamInput(const std::string &config, std::istream &in);

    Command* get_command() override;
    void update() override;

    char get_symb() override;
    std::string get_name() override;

    ~StreamInput() override;
};

#endif