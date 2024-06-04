#ifndef input_interface_h
#define input_interface_h

#include "Command/Command.h"
#include <string>

class InputInterface {
private:
    char symb;
    std::string command_name_;
public:
    virtual ~InputInterface() = default;
    virtual Command* get_command() = 0;
    virtual void update() = 0;
    virtual char get_symb() = 0;
    virtual std::string get_name() = 0;
};

#endif