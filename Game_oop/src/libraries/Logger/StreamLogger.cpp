#include "StreamLogger.h"

StreamLogger :: StreamLogger(std::ostream& out) : out_(out) {}

void StreamLogger :: set_log(MessageInterface* new_log) {
    out_ << *new_log;
}