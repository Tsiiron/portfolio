#ifndef file_logger_h
#define file_logger_h

#include "LoggerInterface.h"
#include <fstream>

class FileLogger : public LoggerInterface {
private:
    std::ofstream out_;
public:
    FileLogger(const std::string& file_name);
    void set_log(MessageInterface* new_log) override;
    ~FileLogger();
};

#endif