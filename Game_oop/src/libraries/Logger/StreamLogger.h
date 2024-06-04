#ifndef stream_logger_h
#define stream_logger_h

#include "LoggerInterface.h"

class StreamLogger : public LoggerInterface {
private:
    std::ostream& out_;
public:
    StreamLogger(std::ostream& out);
    void set_log(MessageInterface* new_log) override;
};

#endif