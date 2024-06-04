#include "Logger.h"

Logger :: Logger() {
    used_[0] = false;
    used_[1] = false;
}

void Logger :: set_log(MessageInterface* new_log) {
    for(auto logger : output_arr_) {
        logger->set_log(new_log);
    }
}

void Logger :: add_logger(int32_t value) {
    switch(value) {
        case 0:
            if(!used_[0]) {
                output_arr_.push_back(new StreamLogger(std::cout));
                used_[0] = true;
            }
            break;
        case 1:
            if(!used_[1]) {
                output_arr_.push_back(new FileLogger("log.txt"));
                used_[1] = true;
            }
            break;
        default:
            break;
    }
}

Logger :: ~Logger() {
    for(auto logger : output_arr_) {
        delete logger;
    }
}