#ifndef logger_interface_h
#define logger_interface_h

#include "Messages/MessageInterface.h"

class LoggerInterface {
public:
    virtual ~LoggerInterface() = default;
    virtual void set_log(MessageInterface* new_log) = 0;
};

#endif