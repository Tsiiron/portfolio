#ifndef message_interface
#define message_interface

#include <iostream>
#include <string>
#include <sstream>

class MessageInterface {
public:
    friend std::ostream& operator<<(std::ostream& out, MessageInterface& msg_interface);
    virtual std::string to_string() = 0;
    virtual ~MessageInterface() = default;
};

#endif