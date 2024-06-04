#ifndef logger_h
#define logger_h

#include "FileLogger.h"
#include "StreamLogger.h"
#include "LoggerInterface.h"
#include <vector>
#include <map>

class Logger {
private:
    std::vector<LoggerInterface*> output_arr_;
    std::map<int32_t, bool> used_;
public:
    Logger();
    void set_log(MessageInterface* new_log);
    void add_logger(int32_t value);
    ~Logger();
};

#endif